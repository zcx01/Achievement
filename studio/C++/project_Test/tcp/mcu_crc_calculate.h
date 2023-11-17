/**
 * @file     crc_calculate.h
 * @author    
 * @date      
 */
#ifndef __MCU_CRC_CALCULATE_H__
#define __MCU_CRC_CALCULATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
/*
 *@brief    calculate 16bits CRC value
 *
 *@argument in_buf :  
 *          in_len :  
 *
 *@return   16bits CRC value
 */
uint16_t crc16_calculate(uint16_t InitValue, uint8_t *DataPtr, uint16_t DataLength, bool IsInitializeEnable);

#ifdef __cplusplus
}
#endif

#endif //__MCU_CRC_CALCULATE_H__
