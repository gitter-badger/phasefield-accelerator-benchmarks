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

/** \addtogroup openacc
 \{
*/

/**
 \file  gpu-openacc-diffusion/discretization.h
 \brief Declaration of discretized mathematical function prototypes for OpenAcc benchmarks
*/

#include "type.h"

#ifndef _DISCRETIZATION_H_
#define _DISCRETIZATION_H_

void set_threads(int n);

void set_mask(fp_t dx, fp_t dy, int nm, fp_t** mask_lap);

void compute_convolution(fp_t** conc_old, fp_t** conc_lap, fp_t** mask_lap,
                         int nx, int ny, int nm);

void solve_diffusion_equation(fp_t** conc_old, fp_t** conc_new, fp_t** conc_lap, int nx,
                              int ny, int nm, fp_t D, fp_t dt, fp_t *elapsed);

void check_solution(fp_t** conc_new, int nx, int ny, fp_t dx, fp_t dy, int nm,
                    fp_t elapsed, fp_t D, fp_t bc[2][2], fp_t* rss);

#endif /* _DISCRETIZATION_H_ */

/** \} */
