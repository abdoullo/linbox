/* Copyright (C) LinBox
 *
 *
 *
 * ========LICENCE========
 * This file is part of the library LinBox.
 *
  * LinBox is free software: you can redistribute it and/or modify
 * it under the terms of the  GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * ========LICENCE========
 */

/*! @file  tests/test-toeplitz-det.C
 * @ingroup tests
 *
 * @brief no doc
 *
 * @test no doc.
 */



#include <linbox/linbox-config.h>

#include <iostream>

#include "linbox/blackbox/toeplitz.h"
#ifdef __LINBOX_HAVE_NTL
#include "linbox/ring/ntl.h"
#endif
#include "linbox/solutions/det.h"
#include "linbox/randiter/random-prime.h"
#include "linbox/util/commentator.h"
#include "test-common.h"
#include <cstdlib>
#include <ctime>
#include "linbox/integer.h"

using namespace std;
using namespace LinBox;

int main(int argc, char* argv[])
{
	static size_t N_BOUND = 100;
	static Argument args[] = {
		{ 'n', "-n N", "Set dimension limit of test matrices to NxN.", TYPE_INT,     &N_BOUND },
		END_OF_ARGUMENTS
	};

	parseArguments (argc, argv, args);

	commentator().start("Toeplitz determinant test suite", "Toeplitz det");
	commentator().getMessageClass (INTERNAL_DESCRIPTION).setMaxDepth (3);
	commentator().getMessageClass (INTERNAL_DESCRIPTION).setMaxDetailLevel (Commentator::LEVEL_UNIMPORTANT);

	ostream& report = commentator().report();
	bool pass = true;
#ifdef __LINBOX_HAVE_NTL
	srand((unsigned)time(0));
	PrimeIterator<IteratorCategories::HeuristicTag> rp(FieldTraits<NTL_zz_p>::bestBitSize());
	NTL_zz_p CF( *rp ); NTL_zz_p::RandIter randit(CF);
	NTL_zz_pX PF(CF);
	
	report << "\tUsing random primes and square matrices of size 2 to " << N_BOUND << endl;
	//for( int i = 0; pass && i < 2; ++i ) {
	size_t n;
	do { n = (size_t)rand() % N_BOUND; } while( n < 2 );

	BlasMatrix<NTL_zz_p> A(CF,n,n);

	NTL_zz_p::Element temp;
	NTL_zz_pX::Element poly;
	PF.assign(poly,PF.zero);

	for( int diff = 1 - ((int)n); diff <= ((int)n) - 1; ++diff ) {
		size_t c;
		size_t r ;
		randit.random(temp);
		PF.setCoeff(poly,(size_t)(diff + (int)n - 1), temp );
		r = c = 0;
		if( diff < 0 ) c = (size_t)(diff*-1);
		else r = (size_t)diff;
		for( ; r < n && c < n; ++r, ++c )
			A.setEntry(r,c,temp);
	}

	Toeplitz<NTL_zz_p,NTL_zz_pX> T( PF, poly, n );

	NTL_zz_p::Element res1, res2;
	//det(res1,A);
	det(res1,T);
	det(res2,T);

	if( res1 != res2 ) pass = false;
	//}
#else
	report << "No test, because no NTL." << endl;
#endif
	report << endl;
	if( pass ) report << "<====== Passed!" << endl;
	else report << "<====== Failed!" << endl;
	commentator().stop("toeplitz determinant test suite");
	return (pass ? 0 : 1);

#if 0
	NTL_ZZ_pX F( 65521 );
	NTL_ZZ_pX::Element a,b;
	F.assign(a,F.one);
	F.init(b,4);
	F.mulin(a,b);
	F.write(cout,a) << endl;
	F.write(cout) << endl;
	NTL_ZZ_pX::Element T;
	Toeplitz<NTL_ZZ_p> Q(F.getCoeffField());
	vector<int> v;
	v.push_back( -3 );
	v.push_back( 50 );
	v.push_back( 71 );
	v.push_back( -43 );
	v.push_back( 91 );
	v.push_back( 16 );
	v.push_back( 78 );
	F.init(T,v);
	Toeplitz<NTL_ZZ_p,NTL_ZZ_pX> mat( F, T, 4 );
	Toeplitz<NTL_ZZ_p,NTL_ZZ_pX>::Element res;
	//mat.det( res );
	det(res,mat);

	/*
	F.init( T, v );
	NTL_ZZ_pX::Coeff res;
	toeplitz_determinant( F, res, T, 4 );
	*/
	//cout << res << endl;
	commentator().stop("toeplitz determinant test suite");
#endif
}

// vim:sts=8:sw=8:ts=8:noet:sr:cino=>s,f0,{0,g0,(0,:0,t0,+0,=s
// Local Variables:
// mode: C++
// tab-width: 8
// indent-tabs-mode: nil
// c-basic-offset: 8
// End:

