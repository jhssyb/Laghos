// Copyright (c) 2017, Lawrence Livermore National Security, LLC. Produced at
// the Lawrence Livermore National Laboratory. LLNL-CODE-734707. All Rights
// reserved. See files LICENSE and NOTICE for details.
//
// This file is part of CEED, a collection of benchmarks, miniapps, software
// libraries and APIs for efficient high-order finite element and spectral
// element discretizations for exascale applications. For more information and
// source code availability see http://github.com/ceed.
//
// The CEED research is supported by the Exascale Computing Project 17-SC-20-SC,
// a collaborative effort of two U.S. Department of Energy organizations (Office
// of Science and the National Nuclear Security Administration) responsible for
// the planning and preparation of a capable exascale ecosystem, including
// software, applications, hardware, advanced system engineering and early
// testbed platforms, in support of the nation's exascale computing imperative.
#include "../hip.hpp"

// *****************************************************************************
extern "C" kernel
void vector_get_subvector0(const int N,
                           double* __restrict v0,
                           const double* __restrict v1,
                           const int* __restrict v2)
{
   const int i = blockDim.x * blockIdx.x + threadIdx.x;
   if (i < N)
   {
      const int dof_i = v2[i];
      v0[i] = dof_i >= 0 ? v1[dof_i] : -v1[-dof_i-1];
   }
}

// *****************************************************************************
void vector_get_subvector(const int N,
                          double* __restrict v0,
                          const double* __restrict v1,
                          const int* __restrict v2)
{
   hipKer(vector_get_subvector,N,v0,v1,v2);
}

