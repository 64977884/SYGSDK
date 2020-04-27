#ifndef  _FILT_ALGORITHM_H_
#define  _FILT_ALGORITHM_H_

#include "stroke_struct.h"

#define ACCDECT (0.5)
#define DECT_NU   3

bool filter_page_code(STROKE_ITEM &stroke);

bool filter_xy_dot_acc(const STROKE_ITEM &stroke, STROKE_ITEM &stroke_no_noise);

bool filt_xy_dot_max_segment(const STROKE_ITEM &stroke_no_noise);

bool filter_algorithm_interface(const STROKE_ITEM &stroke, STROKE_ITEM &stroke_no_noise);

float cal_success_rate_in_a_stroke(const STROKE_ITEM &stroke);

#define FILTER_ALGORITHM_DEBUG_ENABLE		1

typedef struct _pre_stroke_info{
	int page_code;
	unsigned int stroke_start_times_ms;
	unsigned int stroke_start_times_s;
}pre_stroke_info;

extern pre_stroke_info _pre_stroke;

#endif
