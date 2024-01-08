#ifndef __UTILITIES_CRC16_H__
#define __UTILITIES_CRC16_H__

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif
//=================================================================================//
extern uint16_t UTILITY_CRC16_Calculate(uint8_t init_value, const uint8_t data[], uint32_t data_length, bool is_init_enable);
extern uint16_t UTILITY_CRC16_Calculate_x161251(uint16_t init_value, const uint8_t data[], uint32_t data_length, bool is_init_enable, bool post_event);
//=================================================================================//
#ifdef __cplusplus
}
#endif
#endif /* __UTILITIES_CRC16_H__ */