#ifndef _MT_GPIO_FPGA_H_
#define _MT_GPIO_FPGA_H_

//#include <mach/gpio_const.h>
#include <asm/io.h>
#include <mach/sync_write.h>

/* This MACRO define is FAKE, just for compile pass with mt_gpio_debug.c */
#define GPIO_MODE_BITS                 3
#define MAX_GPIO_MODE_PER_REG          5
#define MAX_GPIO_REG_BITS              16

#define GPIO_BASE_1                      0x10005000

#if 0
/* FPGA support code */	
#define INFRA_AO_CFG	0xF0001000
#define MT_GPIO_IN_REG  (INFRA_AO_CFG + 0xE80)
#define MT_GPIO_OUT_REG (INFRA_AO_CFG + 0xE84)
#define MT_GPIO_DIR_REG (INFRA_AO_CFG + 0xE88)
#endif

#if 1
/* This REG structure is FAKE, just depend on the usage of mt_gpio_fpga.c */
struct mt_gpio_vbase {
	void __iomem *gpio_regs;
	void __iomem *IOCFG_L_regs;
	void __iomem *IOCFG_B_regs;
	void __iomem *IOCFG_R_regs;
	void __iomem *IOCFG_T_regs;
	void __iomem *MIPI_TX0_regs;
	void __iomem *MIPI_RX_CSI0_regs;
	void __iomem *MIPI_RX_CSI1_regs;
};

static struct mt_gpio_vbase gpio_vbase;
#endif

/*typedef enum GPIO_PIN
{    
    GPIO_UNSUPPORTED = -1,    
    GPIO0  ,
    GPIO1  , GPIO2  , GPIO3  , GPIO4  , GPIO5  , GPIO6  , GPIO7  , 
    MT_GPIO_BASE_MAX
}GPIO_PIN;*/
/* This MACRO define is FAKE, just for fix build error */
typedef enum GPIO_PIN
{    
    GPIO_UNSUPPORTED = -1,    
    
    GPIO0  , GPIO1  , GPIO2  , GPIO3  , GPIO4  , GPIO5  , GPIO6  , GPIO7  ,
    GPIO8  , GPIO9  , GPIO10 , GPIO11 , GPIO12 , GPIO13 , GPIO14 , GPIO15 ,
    GPIO16 , GPIO17 , GPIO18 , GPIO19 , GPIO20 , GPIO21 , GPIO22 , GPIO23 ,
    GPIO24 , GPIO25 , GPIO26 , GPIO27 , GPIO28 , GPIO29 , GPIO30 , GPIO31 ,
    GPIO32 , GPIO33 , GPIO34 , GPIO35 , GPIO36 , GPIO37 , GPIO38 , GPIO39 ,
    GPIO40 , GPIO41 , GPIO42 , GPIO43 , GPIO44 , GPIO45 , GPIO46 , GPIO47 ,
    GPIO48 , GPIO49 , GPIO50 , GPIO51 , GPIO52 , GPIO53 , GPIO54 , GPIO55 ,
    GPIO56 , GPIO57 , GPIO58 , GPIO59 , GPIO60 , GPIO61 , GPIO62 , GPIO63 ,
    GPIO64 , GPIO65 , GPIO66 , GPIO67 , GPIO68 , GPIO69 , GPIO70 , GPIO71 ,
    GPIO72 , GPIO73 , GPIO74 , GPIO75 , GPIO76 , GPIO77 , GPIO78 , GPIO79 ,
    GPIO80 , GPIO81 , GPIO82 , GPIO83 , GPIO84 , GPIO85 , GPIO86 , GPIO87 ,
    GPIO88 , GPIO89 , GPIO90 , GPIO91 , GPIO92 , GPIO93 , GPIO94 , GPIO95 ,
    GPIO96 , GPIO97 , GPIO98 , GPIO99 , GPIO100, GPIO101, GPIO102, GPIO103,
    GPIO104, GPIO105, GPIO106, GPIO107, GPIO108, GPIO109, GPIO110, GPIO111,
    GPIO112, GPIO113, GPIO114, GPIO115, GPIO116, GPIO117, GPIO118, GPIO119,
    GPIO120, GPIO121, GPIO122, GPIO123, GPIO124, GPIO125, GPIO126, GPIO127,
    GPIO128, GPIO129, GPIO130, GPIO131, GPIO132, GPIO133, GPIO134, GPIO135,
    GPIO136, GPIO137, GPIO138, GPIO139, GPIO140, GPIO141, GPIO142, GPIO143,
    GPIO144, GPIO145, GPIO146, GPIO147, GPIO148, GPIO149, GPIO150, GPIO151,
    GPIO152, GPIO153, GPIO154,  MT_GPIO_BASE_MAX
}GPIO_PIN;
#define MT_GPIO_BASE_START GPIO0
#define MT_GPIO_EXT_START  MT_GPIO_BASE_MAX

typedef enum GPIO_PIN_EXT
{    
    MT_GPIO_EXT_MAX = MT_GPIO_EXT_START
}GPIO_PIN_EXT;    
#define MT_GPIO_MAX_PIN MT_GPIO_EXT_MAX


/* This REG structure is FAKE, just for compile pass with mt_gpio_debug.c */
typedef struct {        
    unsigned short val;        
    unsigned short _align1;
    unsigned short set;
    unsigned short _align2;
    unsigned short rst;
    unsigned short _align3[3];
} VAL_REGS;
typedef struct {
    VAL_REGS    dir[10];            /*0x0000 ~ 0x009F: 160 bytes*/
    VAL_REGS    pullen[10];         /*0x0100 ~ 0x019F: 160 bytes*/
    VAL_REGS    pullsel[10];        /*0x0200 ~ 0x029F: 160 bytes*/
    VAL_REGS    dout[10];           /*0x0400 ~ 0x049F: 160bytes*/
    VAL_REGS    din[10];            /*0x0500 ~ 0x059F: 160 bytes*/
    VAL_REGS    mode[31];           /*0x0600 ~ 0x07EF: 496bytes*/  
	VAL_REGS    ies[2];            	/*0x0900 ~ 0x091F: 	32 bytes*/
} GPIO_REGS;
/*----------------------------------------------------------------------------*/

#endif //_MT_GPIO_FPGA_H_
