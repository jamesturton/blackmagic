/*
 * This file is part of the Black Magic Debug project.
 *
 * Copyright (C) 2022 1BitSquared <info@1bitsquared.com>
 * Written by Rachel Mant <git@dragonmux.network>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PLATFORMS_COMMON_USB_H
#define PLATFORMS_COMMON_USB_H

#include <stdint.h>
#include <libopencm3/usb/usbd.h>

extern usbd_device *usbdev;
extern uint16_t usb_config;

#if defined(USB_HS)
# define CDCACM_PACKET_SIZE 512
#else
# define CDCACM_PACKET_SIZE 64
#endif

#if !defined(MAX_BINTERVAL)
# define MAX_BINTERVAL 255
#endif

#define TRACE_ENDPOINT_SIZE CDCACM_PACKET_SIZE

/* Use platform provided value if given. */
#if !defined(TRACE_ENDPOINT_SIZE)
# define TRACE_ENDPOINT_SIZE CDCACM_PACKET_SIZE
#endif

#define CDCACM_GDB_ENDPOINT   1
#define CDCACM_UART_ENDPOINT  3
#define TRACE_ENDPOINT        5
#define CDCACM_SLCAN_ENDPOINT 6

#define GDB_IF_NO  0
#define UART_IF_NO 2
#define DFU_IF_NO  4
#if defined(PLATFORM_HAS_SLCAN)
# define TRACE_IF_NO 5
# define SLCAN_IF_NO 6
# define TOTAL_INTERFACES  8
#elif defined(PLATFORM_HAS_TRACESWO)
#define TRACE_IF_NO      5
#define TOTAL_INTERFACES 6
#else
#define TOTAL_INTERFACES 5
#endif

void blackmagic_usb_init(void);

/* Returns current usb configuration, or 0 if not configured. */
uint16_t usb_get_config(void);

#endif /* PLATFORMS_COMMON_USB_H */
