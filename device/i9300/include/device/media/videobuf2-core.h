/*
 * videobuf2-core.h - V4L2 driver helper framework
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Pawel Osciak <pawel@osciak.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */
#ifndef _MEDIA_VIDEOBUF2_CORE_H
#define _MEDIA_VIDEOBUF2_CORE_H

#include <linux/mm_types.h>
#include <linux/mutex.h>
#include <linux/poll.h>
#include <device/linux/videodev2.h>
#include <linux/dma-buf.h>

struct vb2_alloc_ctx;
struct vb2_fileio_data;

/**
 * struct vb2_mem_ops - memory handling/memory allocator operations
 * @alloc:	allocate video memory and, optionally, allocator private data,
 *		return NULL on failure or a pointer to allocator private,
 *		per-buffer data on success; the returned private structure
 *		will then be passed as buf_priv argument to other ops in this
 *		structure
 * @put:	inform the allocator that the buffer will no longer be used;
 *		usually will result in the allocator freeing the buffer (if
 *		no other users of this buffer are present); the buf_priv
 *		argument is the allocator private per-buffer structure
 *		previously returned from the alloc callback
 * @get_userptr: acquire userspace memory for a hardware operation; used for
 *		 USERPTR memory types; vaddr is the address passed to the
 *		 videobuf layer when queuing a video buffer of USERPTR type;
 *		 should return an allocator private per-buffer structure
 *		 associated with the buffer on success, NULL on failure;
 *		 the returned private structure will then be passed as buf_priv
 *		 argument to other ops in this structure
 * @put_userptr: inform the allocator that a USERPTR buffer will no longer
 *		 be used
 * @attach_dmabuf: attach a shared struct dma_buf for a hardware operation;
 *		used for DMABUF memory types; alloc_ctx is the alloc context
 *		dbuf is the shared dma_buf; returns NULL on failure;
 *		allocator private per-buffer structure on success;
 *		this needs to be used for further accesses to the buffer.
 * @detach_dmabuf: inform the exporter of the buffer that the current DMABUF
 *		buffer is no longer used; the buf_priv argument is the
 *		allocator private per-buffers structure previously returned
 *		from the attach_dmabuf callback.
 * @map_dmabuf: request for access to the dmabuf from allocator; the allocator
 *		of dmabuf is informed that this driver is going to use the
 *		dmabuf.
 * @unmap_dmabuf: releases access control to the dmabuf - allocator is notified
 *		that this driver is done using the dmabuf for now.
 * @export_dmabuf: export an allocated buffer to the dmabuf for that user can
 *		access the buffer through the fd of it.
 * @vaddr:	return a kernel virtual address to a given memory buffer
 *		associated with the passed private structure or NULL if no
 *		such mapping exists
 * @cookie:	return allocator specific cookie for a given memory buffer
 *		associated with the passed private structure or NULL if not
 *		available
 * @share:	return allocator specific object to share a given memory buffer
 *		associated with the passed private structure or NULL if not
 *		available
 * @num_users:	return the current number of users of a memory buffer;
 *		return 1 if the videobuf layer (or actually the driver using
 *		it) is the only user
 * @mmap:	setup a userspace mapping for a given memory buffer under
 *		the provided virtual memory region
 * @sync_to_dev: change the ownership of the buffer from CPU to device; this
 *               ensures that all stuffs related to the buffer visible to CPU
 *		 are also visible to the device.
 * @sync_from_dev: change the ownership of the buffer from device to CPU; this
 *                 ensures that all stuffs related to the buffer visible to
 *                 the device are also visible to the CPU.
 *
 * Required ops for USERPTR types: get_userptr, put_userptr.
 * Required ops for MMAP types: alloc, put, num_users, mmap.
 * Required ops for read/write access types: alloc, put, num_users, vaddr
 * Required ops for DMABUF types: attach_dmabuf, detach_dmabuf, map_dmabuf,
 *				  unmap_dmabuf, export_dmabuf.
 */
struct vb2_mem_ops {
	void		*(*alloc)(void *alloc_ctx, unsigned long size);
	void		(*put)(void *buf_priv);

	void		*(*get_userptr)(void *alloc_ctx, unsigned long vaddr,
					unsigned long size, int write);
	void		(*put_userptr)(void *buf_priv);

	int		(*export_dmabuf)(void *alloc_ctx, void *buf_priv,
						int *export_fd);

	/*
	 * XXX really, I think the attach/detach could be handled in the
	 * vb2 core, and vb2_mem_ops really just need to get/put the sglist
	 * (and make sure that the sglist fits it's needs..)
	 */
	void		*(*attach_dmabuf)(void *alloc_ctx,
						struct dma_buf *dbuf);
	void		(*detach_dmabuf)(void *buf_priv);
	void		(*map_dmabuf)(void *buf_priv);
	void		(*unmap_dmabuf)(void *buf_priv);

	void		*(*vaddr)(void *buf_priv);
	void		*(*cookie)(void *buf_priv);
	void		*(*share)(void *buf_priv);

	unsigned int	(*num_users)(void *buf_priv);

	int		(*mmap)(void *buf_priv, struct vm_area_struct *vma);
	void		(*sync_to_dev)(void *alloc_ctx[], void *privs[],
					int nplanes, enum v4l2_buf_type type);
	void		(*sync_from_dev)(void *alloc_ctx[], void *privs[],
					int nplanes, enum v4l2_buf_type type);
};

struct vb2_plane {
	void			*mem_priv;
	struct dma_buf		*dbuf;
	int			mapped:1;
};

/**
 * enum vb2_io_modes - queue access methods
 * @VB2_MMAP:		driver supports MMAP with streaming API
 * @VB2_USERPTR:	driver supports USERPTR with streaming API
 * @VB2_READ:		driver supports read() style access
 * @VB2_WRITE:		driver supports write() style access
 * @VB2_DMABUF:		driver supports DMABUF with streaming API
 */
enum vb2_io_modes {
	VB2_MMAP	= (1 << 0),
	VB2_USERPTR	= (1 << 1),
	VB2_READ	= (1 << 2),
	VB2_WRITE	= (1 << 3),
	VB2_DMABUF	= (1 << 4),
};

/**
 * enum vb2_fileio_flags - flags for selecting a mode of the file io emulator,
 * by default the 'streaming' style is used by the file io emulator
 * @VB2_FILEIO_READ_ONCE:	report EOF after reading the first buffer
 * @VB2_FILEIO_WRITE_IMMEDIATELY:	queue buffer after each write() call
 */
enum vb2_fileio_flags {
	VB2_FILEIO_READ_ONCE		= (1 << 0),
	VB2_FILEIO_WRITE_IMMEDIATELY	= (1 << 1),
};

/**
 * enum vb2_buffer_state - current video buffer state
 * @VB2_BUF_STATE_DEQUEUED:	buffer under userspace control
 * @VB2_BUF_STATE_PREPARED:	buffer prepared in videobuf and by the driver
 * @VB2_BUF_STATE_QUEUED:	buffer queued in videobuf, but not in driver
 * @VB2_BUF_STATE_ACTIVE:	buffer queued in driver and possibly used
 *				in a hardware operation
 * @VB2_BUF_STATE_DONE:		buffer returned from driver to videobuf, but
 *				not yet dequeued to userspace
 * @VB2_BUF_STATE_ERROR:	same as above, but the operation on the buffer
 *				has ended with an error, which will be reported
 *				to the userspace when it is dequeued
 */
enum vb2_buffer_state {
	VB2_BUF_STATE_DEQUEUED,
	VB2_BUF_STATE_PREPARED,
	VB2_BUF_STATE_QUEUED,
	VB2_BUF_STATE_ACTIVE,
	VB2_BUF_STATE_DONE,
	VB2_BUF_STATE_ERROR,
};

struct vb2_queue;

/**
 * struct vb2_buffer - represents a video buffer
 * @v4l2_buf:		struct v4l2_buffer associated with this buffer; can
 *			be read by the driver and relevant entries can be
 *			changed by the driver in case of CAPTURE types
 *			(such as timestamp)
 * @v4l2_planes:	struct v4l2_planes associated with this buffer; can
 *			be read by the driver and relevant entries can be
 *			changed by the driver in case of CAPTURE types
 *			(such as bytesused); NOTE that even for single-planar
 *			types, the v4l2_planes[0] struct should be used
 *			instead of v4l2_buf for filling bytesused - drivers
 *			should use the vb2_set_plane_payload() function for that
 * @vb2_queue:		the queue to which this driver belongs
 * @num_planes:		number of planes in the buffer
 *			on an internal driver queue
 * @state:		current buffer state; do not change
 * @queued_entry:	entry on the queued buffers list, which holds all
 *			buffers queued from userspace
 * @done_entry:		entry on the list that stores all buffers ready to
 *			be dequeued to userspace
 * @planes:		private per-plane information; do not change
 * @num_planes_mapped:	number of mapped planes; do not change
 */
struct vb2_buffer {
	struct v4l2_buffer	v4l2_buf;
	struct v4l2_plane	v4l2_planes[VIDEO_MAX_PLANES];

	struct vb2_queue	*vb2_queue;

	unsigned int		num_planes;

/* Private: internal use only */
	enum vb2_buffer_state	state;

	struct list_head	queued_entry;
	struct list_head	done_entry;

	struct vb2_plane	planes[VIDEO_MAX_PLANES];
	unsigned int		num_planes_mapped;
};

/**
 * struct vb2_ops - driver-specific callbacks
 *
 * @queue_setup:	called from VIDIOC_REQBUFS and VIDIOC_CREATE_BUFS
 *			handlers before memory allocation, or, if
 *			*num_planes != 0, after the allocation to verify a
 *			smaller number of buffers. Driver should return
 *			the required number of buffers in *num_buffers, the
 *			required number of planes per buffer in *num_planes; the
 *			size of each plane should be set in the sizes[] array
 *			and optional per-plane allocator specific context in the
 *			alloc_ctxs[] array. When called from VIDIOC_REQBUFS,
 *			fmt == NULL, the driver has to use the currently
 *			configured format and *num_buffers is the total number
 *			of buffers, that are being allocated. When called from
 *			VIDIOC_CREATE_BUFS, fmt != NULL and it describes the
 *			target frame format. In this case *num_buffers are being
 *			allocated additionally to q->num_buffers.
 * @wait_prepare:	release any locks taken while calling vb2 functions;
 *			it is called before an ioctl needs to wait for a new
 *			buffer to arrive; required to avoid a deadlock in
 *			blocking access type
 * @wait_finish:	reacquire all locks released in the previous callback;
 *			required to continue operation after sleeping while
 *			waiting for a new buffer to arrive
 * @buf_init:		called once after allocating a buffer (in MMAP case)
 *			or after acquiring a new USERPTR buffer; drivers may
 *			perform additional buffer-related initialization;
 *			initialization failure (return != 0) will prevent
 *			queue setup from completing successfully; optional
 * @buf_prepare:	called every time the buffer is queued from userspace
 *			and from the VIDIOC_PREPARE_BUF ioctl; drivers may
 *			perform any initialization required before each hardware
 *			operation in this callback; if an error is returned, the
 *			buffer will not be queued in driver; optional
 * @buf_finish:		called before every dequeue of the buffer back to
 *			userspace; drivers may perform any operations required
 *			before userspace accesses the buffer; optional
 * @buf_cleanup:	called once before the buffer is freed; drivers may
 *			perform any additional cleanup; optional
 * @start_streaming:	called once before entering 'streaming' state; enables
 *			driver to receive buffers over buf_queue() callback
 * @stop_streaming:	called when 'streaming' state must be disabled; driver
 *			should stop any DMA transactions or wait until they
 *			finish and give back all buffers it got from buf_queue()
 *			callback; may use vb2_wait_for_all_buffers() function
 * @buf_queue:		passes buffer vb to the driver; driver may start
 *			hardware operation on this buffer; driver should give
 *			the buffer back by calling vb2_buffer_done() function
 */
struct vb2_ops {
	int (*queue_setup)(struct vb2_queue *q, unsigned int *num_buffers,
			   unsigned int *num_planes, unsigned long sizes[],
			   void *alloc_ctxs[]);

	void (*wait_prepare)(struct vb2_queue *q);
	void (*wait_finish)(struct vb2_queue *q);

	int (*buf_init)(struct vb2_buffer *vb);
	int (*buf_prepare)(struct vb2_buffer *vb);
	int (*buf_finish)(struct vb2_buffer *vb);
	void (*buf_cleanup)(struct vb2_buffer *vb);

	int (*start_streaming)(struct vb2_queue *q);
	int (*stop_streaming)(struct vb2_queue *q);

	void (*buf_queue)(struct vb2_buffer *vb);
};

/**
 * struct vb2_queue - a videobuf queue
 *
 * @type:	queue type (see V4L2_BUF_TYPE_* in linux/videodev2.h
 * @io_modes:	supported io methods (see vb2_io_modes enum)
 * @io_flags:	additional io flags (see vb2_fileio_flags enum)
 * @ops:	driver-specific callbacks
 * @mem_ops:	memory allocator specific callbacks
 * @drv_priv:	driver private data
 * @buf_struct_size: size of the driver-specific buffer structure;
 *		"0" indicates the driver doesn't want to use a custom buffer
 *		structure type, so sizeof(struct vb2_buffer) will is used
 *
 * @memory:	current memory type used
 * @bufs:	videobuf buffer structures
 * @num_buffers: number of allocated/used buffers
 * @queued_list: list of buffers currently queued from userspace
 * @queued_count: number of buffers owned by the driver
 * @done_list:	list of buffers ready to be dequeued to userspace
 * @done_lock:	lock to protect done_list list
 * @done_wq:	waitqueue for processes waiting for buffers ready to be dequeued
 * @alloc_ctx:	memory type/allocator-specific contexts for each plane
 * @streaming:	current streaming state
 * @fileio:	file io emulator internal data, used only if emulator is active
 */
struct vb2_queue {
	enum v4l2_buf_type		type;
	unsigned int			io_modes;
	unsigned int			io_flags;

	const struct vb2_ops		*ops;
	const struct vb2_mem_ops	*mem_ops;
	void				*drv_priv;
	unsigned int			buf_struct_size;

/* private: internal use only */
	enum v4l2_memory		memory;
	struct vb2_buffer		*bufs[VIDEO_MAX_FRAME];
	unsigned int			num_buffers;

	struct list_head		queued_list;

	atomic_t			queued_count;
	struct list_head		done_list;
	spinlock_t			done_lock;
	wait_queue_head_t		done_wq;

	void				*alloc_ctx[VIDEO_MAX_PLANES];

	unsigned int			streaming:1;

	struct vb2_fileio_data		*fileio;
};

void *vb2_plane_vaddr(struct vb2_buffer *vb, unsigned int plane_no);
void *vb2_plane_cookie(struct vb2_buffer *vb, unsigned int plane_no);

void vb2_buffer_done(struct vb2_buffer *vb, enum vb2_buffer_state state);
int vb2_wait_for_all_buffers(struct vb2_queue *q);

int vb2_querybuf(struct vb2_queue *q, struct v4l2_buffer *b);
int vb2_reqbufs(struct vb2_queue *q, struct v4l2_requestbuffers *req);

int vb2_create_bufs(struct vb2_queue *q, struct v4l2_create_buffers *create);
int vb2_prepare_buf(struct vb2_queue *q, struct v4l2_buffer *b);

int vb2_queue_init(struct vb2_queue *q);

void vb2_queue_release(struct vb2_queue *q);

int vb2_qbuf(struct vb2_queue *q, struct v4l2_buffer *b);
int vb2_dqbuf(struct vb2_queue *q, struct v4l2_buffer *b, bool nonblocking);

int vb2_streamon(struct vb2_queue *q, enum v4l2_buf_type type);
int vb2_streamoff(struct vb2_queue *q, enum v4l2_buf_type type);

int vb2_mmap(struct vb2_queue *q, struct vm_area_struct *vma);
#ifndef CONFIG_MMU
unsigned long vb2_get_unmapped_area(struct vb2_queue *q,
				    unsigned long addr,
				    unsigned long len,
				    unsigned long pgoff,
				    unsigned long flags);
#endif
unsigned int vb2_poll(struct vb2_queue *q, struct file *file, poll_table *wait);
size_t vb2_read(struct vb2_queue *q, char __user *data, size_t count,
		loff_t *ppos, int nonblock);
size_t vb2_write(struct vb2_queue *q, char __user *data, size_t count,
		loff_t *ppos, int nonblock);

/**
 * vb2_is_streaming() - return streaming status of the queue
 * @q:		videobuf queue
 */
static inline bool vb2_is_streaming(struct vb2_queue *q)
{
	return q->streaming;
}

/**
 * vb2_is_busy() - return busy status of the queue
 * @q:		videobuf queue
 *
 * This function checks if queue has any buffers allocated.
 */
static inline bool vb2_is_busy(struct vb2_queue *q)
{
	return (q->num_buffers > 0);
}

/**
 * vb2_get_drv_priv() - return driver private data associated with the queue
 * @q:		videobuf queue
 */
static inline void *vb2_get_drv_priv(struct vb2_queue *q)
{
	return q->drv_priv;
}

/**
 * vb2_set_plane_payload() - set bytesused for the plane plane_no
 * @vb:		buffer for which plane payload should be set
 * @plane_no:	plane number for which payload should be set
 * @size:	payload in bytes
 */
static inline void vb2_set_plane_payload(struct vb2_buffer *vb,
				 unsigned int plane_no, unsigned long size)
{
	if (plane_no < vb->num_planes)
		vb->v4l2_planes[plane_no].bytesused = size;
}

/**
 * vb2_get_plane_payload() - get bytesused for the plane plane_no
 * @vb:		buffer for which plane payload should be set
 * @plane_no:	plane number for which payload should be set
 * @size:	payload in bytes
 */
static inline unsigned long vb2_get_plane_payload(struct vb2_buffer *vb,
				 unsigned int plane_no)
{
	if (plane_no < vb->num_planes)
		return vb->v4l2_planes[plane_no].bytesused;
	return 0;
}

/**
 * vb2_plane_size() - return plane size in bytes
 * @vb:		buffer for which plane size should be returned
 * @plane_no:	plane number for which size should be returned
 */
static inline unsigned long
vb2_plane_size(struct vb2_buffer *vb, unsigned int plane_no)
{
	if (plane_no < vb->num_planes)
		return vb->v4l2_planes[plane_no].length;
	return 0;
}

#endif /* _MEDIA_VIDEOBUF2_CORE_H */
