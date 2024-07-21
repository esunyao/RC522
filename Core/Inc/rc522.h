//
// Created by Esuny on 2024/7/21.
//

#ifndef RC522_RC522_H
#define RC522_RC522_H


#include "stm32f1xx_hal.h"

#define    uchar    unsigned char
#define    uint    unsigned int
extern SPI_HandleTypeDef hspi1;

//Maximum length of the array
// 数组的最大长度
#define MAX_LEN 16

#define HSPI_INSTANCE                &hspi1
#define MFRC522_CS_PORT                GPIOA
#define MFRC522_CS_PIN                GPIO_PIN_4
#define MFRC522_RST_PORT            GPIOB
#define MFRC522_RST_PIN                GPIO_PIN_0

// MFRC522 命令。数据表第 10 章中进行了描述。
#define PCD_IDLE              0x00               // 无操作，取消当前命令执行
#define PCD_AUTHENT           0x0E               // 作为读卡器执行 MIFARE 标准身份验证
#define PCD_RECEIVE           0x08               // 激活接收器电路
#define PCD_TRANSMIT          0x04               // 从 FIFO 缓冲区传输数据
#define PCD_TRANSCEIVE        0x0C               // 将数据从 FIFO 缓冲区传输到天线，并在传输后自动激活接收器
#define PCD_RESETPHASE        0x0F               // 重置 MFRC522
#define PCD_CALCCRC           0x03               // 激活 CRC 协处理器或执行自检

// 命令发送至 PICC。
#define PICC_REQIDL           0x26               // REQuest 命令，类型 A。邀请处于 IDLE 状态的 PICC 进入 READY 状态并准备防冲突或选择。 7 位帧。
#define PICC_REQALL           0x52               // 唤醒命令，类型 A。邀请处于 IDLE 和 HALT 状态的 PICC 进入 READY(*) 状态并准备防冲突或选择。 7 位帧。
#define PICC_ANTICOLL         0x93               // 防碰撞/选择，级联级别 1
#define PICC_SElECTTAG        0x93               // 防碰撞/选择，级联级别 2
#define PICC_AUTHENT1A        0x60               // 使用密钥 A 进行认证
#define PICC_AUTHENT1B        0x61               // 使用密钥 B 进行认证
#define PICC_READ             0x30               // 从已认证的扇区读取一个 16 字节的块。也用于 MIFARE Ultralight。
#define PICC_WRITE            0xA0               // 向已认证的扇区写入一个 16 字节的块。对于 MIFARE Ultralight 称为“兼容性写入”。
#define PICC_DECREMENT        0xC0               // 减少块的内容并将结果存储在内部数据寄存器中。
#define PICC_INCREMENT        0xC1               // 增加块的内容并将结果存储在内部数据寄存器中。
#define PICC_RESTORE          0xC2               // 将块的内容读入内部数据寄存器。
#define PICC_TRANSFER         0xB0               // 将内部数据寄存器的内容写入一个块。
#define PICC_HALT             0x50               // HALT 命令，类型 A。指示一个活动的 PICC 进入 HALT 状态。


// 通讯时返回成功或错误码
#define MI_OK                 0
#define MI_NOTAGERR           1
#define MI_ERR                2


// MFRC522 寄存器。数据表第 9 章中进行了描述。
// 第 0 页 命令和状态
#define     Reserved00            0x00
#define     CommandReg            0x01
#define     CommIEnReg            0x02
#define     DivlEnReg             0x03
#define     CommIrqReg            0x04
#define     DivIrqReg             0x05
#define     ErrorReg              0x06
#define     Status1Reg            0x07
#define     Status2Reg            0x08
#define     FIFODataReg           0x09
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     Reserved01            0x0F
//第 1 页 命令
#define     Reserved10            0x10
#define     ModeReg               0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     Reserved11            0x1A
#define     Reserved12            0x1B
#define     MifareReg             0x1C
#define     Reserved13            0x1D
#define     Reserved14            0x1E
#define     SerialSpeedReg        0x1F
//第 2 页 配置
#define     Reserved20            0x20
#define     CRCResultRegH         0x21
#define     CRCResultRegL         0x22
#define     Reserved21            0x23
#define     ModWidthReg           0x24
#define     Reserved22            0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsPReg              0x28
#define     ModGsPReg             0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F
//第 3 页 测试寄存器
#define     Reserved30            0x30
#define     TestSel1Reg           0x31
#define     TestSel2Reg           0x32
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34
#define     TestBusReg            0x35
#define     AutoTestReg           0x36
#define     VersionReg            0x37
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39
#define     TestDAC2Reg           0x3A
#define     TestADCReg            0x3B
#define     Reserved31            0x3C
#define     Reserved32            0x3D
#define     Reserved33            0x3E
#define     Reserved34              0x3F

// 用于操作 MFRC522 的功能
void MFRC522_Init(void);

uchar MFRC522_Request(uchar reqMode, uchar *TagType);

uchar MFRC522_Anticoll(uchar *serNum);

uchar MFRC522_SelectTag(uchar *serNum);

uchar MFRC522_Auth(uchar authMode, uchar BlockAddr, uchar *Sectorkey, uchar *serNum);

uchar MFRC522_Write(uchar blockAddr, uchar *writeData);

uchar MFRC522_Auth(uchar authMode, uchar BlockAddr, uchar *Sectorkey, uchar *serNum);

uchar MFRC522_Read(uchar blockAddr, uchar *recvData);

void MFRC522_Halt(void);


#endif //RC522_RC522_H
