/*
 * This file is part of the Black Magic Debug project.
 *
 * MIT License
 *
 * Copyright (c) 2021 Koen De Vleeschauwer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef INCLUDE_RTT_H
#define INCLUDE_RTT_H
#include <target.h>

#define MAX_RTT_CHAN 16

extern char rtt_ident[16];	    // string
extern bool rtt_enabled;	    // rtt on/off
extern bool rtt_found;              // control block found
extern uint32_t rtt_cbaddr;         // control block address
extern uint32_t rtt_min_poll_ms;    // min time between polls (ms)
extern uint32_t rtt_max_poll_ms;    // max time between polls (ms)
extern uint32_t rtt_max_poll_errs;  // max number of errors before disconnect
extern bool rtt_auto_channel;       // manual or auto channel selection
extern bool rtt_flag_skip;          // skip if host-to-target fifo full
extern bool rtt_flag_block;         // block if host-to-target fifo full

struct rtt_channel_struct {
	bool is_enabled;            // does user want to see this channel?
	bool is_configured;         // is channel configured in control block?
	bool is_output;
	uint32_t buf_addr;
	uint32_t buf_size;
	uint32_t head_addr;
	uint32_t tail_addr;
	uint32_t flag;
};

extern struct rtt_channel_struct rtt_channel[MAX_RTT_CHAN];

// true if target memory access does not work when target running
bool target_no_background_memory_access(target *cur_target);
void poll_rtt(target *cur_target);

#endif /* INCLUDE_RTT_H */
