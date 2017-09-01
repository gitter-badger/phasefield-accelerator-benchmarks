/**********************************************************************************
 This file is part of Phase-field Accelerator Benchmarks, written by Trevor Keller
 and available from https://github.com/usnistgov/phasefield-accelerator-benchmarks.

 This software was developed at the National Institute of Standards and Technology
 by employees of the Federal Government in the course of their official duties.
 Pursuant to title 17 section 105 of the United States Code this software is not
 subject to copyright protection and is in the public domain. NIST assumes no
 responsibility whatsoever for the use of this software by other parties, and makes
 no guarantees, expressed or implied, about its quality, reliability, or any other
 characteristic. We would appreciate acknowledgement if the software is used.

 This software can be redistributed and/or modified freely provided that any
 derivative works bear some notice that they are derived from it, and any modified
 versions bear some notice that they have been modified.

 Questions/comments to Trevor Keller (trevor.keller@nist.gov)
 **********************************************************************************/

/**
 \file  common-diffusion/numerics.h
 \brief Declaration of Laplacian operator and analytical solution functions
*/

#include "type.h"

#ifndef _NUMERICS_H_
#define _NUMERICS_H_

/**
 \brief Maximum width of the convolution mask (Laplacian stencil) array
*/
#define MAX_MASK_W 5

/**
 \brief Maximum height of the convolution mask (Laplacian stencil) array
*/
#define MAX_MASK_H 5

void set_mask(fp_t dx, fp_t dy, int code, fp_t** mask_lap, int nm);

void five_point_Laplacian_stencil(fp_t dx, fp_t dy, fp_t** mask_lap, int nm);

void nine_point_Laplacian_stencil(fp_t dx, fp_t dy, fp_t** mask_lap, int nm);

void slow_nine_point_Laplacian_stencil(fp_t dx, fp_t dy, fp_t** mask_lap, int nm);

#ifdef _OPENACC
#pragma acc routine worker nohost
#endif
fp_t euclidean_distance(fp_t ax, fp_t ay, fp_t bx, fp_t by);

#ifdef _OPENACC
#pragma acc routine worker nohost
#endif
fp_t manhattan_distance(fp_t ax, fp_t ay, fp_t bx, fp_t by);

#ifdef _OPENACC
#pragma acc routine worker nohost
#endif
fp_t distance_point_to_segment(fp_t ax, fp_t ay, fp_t bx, fp_t by, fp_t px, fp_t py);

void analytical_value(fp_t x, fp_t t, fp_t D, fp_t bc[2][2], fp_t* c);

#endif /* _NUMERICS_H_ */
