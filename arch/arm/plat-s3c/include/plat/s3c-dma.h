/* linux/arch/arm/plat-s3c/include/plat/dma.h
 *
 */

#ifndef __ARM_PLAT_S3C_DMA_H
#define __ARM_PLAT_S3C_DMA_H 

extern struct sysdev_class dma_sysclass;
extern struct s3c2410_dma_chan s3c2410_chans[S3C_DMA_CHANNELS];

#define DMA_CH_VALID		(1<<31)
#define DMA_CH_NEVER		(1<<30)

struct s3c_dma_addr {
	unsigned long		from;
	unsigned long		to;
};

/* struct s3c_dma_map
 *
 * this holds the mapping information for the channel selected
 * to be connected to the specified device
*/

struct s3c_dma_map {
	const char		*name;
	struct s3c_dma_addr  	hw_addr;

	unsigned long		channels[S3C_DMA_CHANNELS];
	unsigned long		channels_rx[S3C_DMA_CHANNELS];

        unsigned long            sdma_sel;
};

struct s3c_dma_selection {
	struct s3c_dma_map	*map;
	unsigned long		 map_size;
	unsigned long		 dcon_mask;

	void	(*select)(struct s3c2410_dma_chan *chan,
			  struct s3c_dma_map *map);

	void	(*direction)(struct s3c2410_dma_chan *chan,
			     struct s3c_dma_map *map,
			     enum s3c2410_dmasrc dir);
};

extern int s3c_dma_init_map(struct s3c_dma_selection *sel);

/* struct s3c_dma_order_ch
 *
 * channel map for one of the `enum dma_ch` dma channels. the list
 * entry contains a set of low-level channel numbers, orred with
 * DMA_CH_VALID, which are checked in the order in the array.
*/

struct s3c_dma_order_ch {
	unsigned int	list[S3C_DMA_CHANNELS];	/* list of channels */
	unsigned int	flags;				/* flags */
};

/* struct s3c_dma_order
 *
 * information provided by either the core or the board to give the
 * dma system a hint on how to allocate channels
*/

struct s3c_dma_order {
	struct s3c_dma_order_ch	channels[DMACH_MAX];
};

extern int s3c_dma_order_set(struct s3c_dma_order *map);

/* DMA init code, called from the cpu support code */

extern int s3c_dma_init(unsigned int channels, unsigned int irq,
			    unsigned int stride);
#endif //__ARM_PLAT_S3C_DMA_H
