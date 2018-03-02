/*################################################################################
  ##
  ##   Copyright (C) 2011-2018 Keith O'Hara
  ##
  ##   This file is part of the StatsLib C++ library.
  ##
  ##   Licensed under the Apache License, Version 2.0 (the "License");
  ##   you may not use this file except in compliance with the License.
  ##   You may obtain a copy of the License at
  ##
  ##       http://www.apache.org/licenses/LICENSE-2.0
  ##
  ##   Unless required by applicable law or agreed to in writing, software
  ##   distributed under the License is distributed on an "AS IS" BASIS,
  ##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ##   See the License for the specific language governing permissions and
  ##   limitations under the License.
  ##
  ################################################################################*/

/* 
 * Sample from a Wishart distribution
 */

template<typename mT, typename eT>
mT
rwish(const mT& Psi_par, const eT nu_par, const bool pre_chol)
{
    const uint_t K = mat_ops::n_rows(Psi_par);
    
    mT chol_Psi;
    if (pre_chol) {
        chol_Psi = Psi_par; // should be lower triangular
    } else {
        chol_Psi = mat_ops::chol(Psi_par); // will be lower triangular
    }

    //

    mT A;
    mat_ops::zeros(A,K,K);

    for (uint_t i=1U; i < K; i++) {
        for (uint_t j=0U; j < i; j++) {
            A(i,j) = rnorm<eT>();
        }
    }
    
    for (uint_t i=0U; i < K; i++) {
        A(i,i) = std::sqrt(rchisq<eT>(nu_par-i));
    }

    chol_Psi = chol_Psi*A;

    //
    
    return chol_Psi * mat_ops::trans(chol_Psi);
}
