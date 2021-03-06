/* lb-rank.C
 * Copyright (C) 2005 Pascal Giorgi
 *
 * Written by Pascal Giorgi <pgiorgi@uwaterloo.ca>
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

#ifndef __LINBOX_lb_rank_C
#define __LINBOX_lb_rank_C


#include "linbox/solutions/rank.h"

#include <lb-rank.h>
#include <lb-blackbox-function.h>


extern BlackboxTable blackbox_hashtable;

/****************
 * Rank Functor *
 ****************/
template<typename Method= LinBox::Method::Hybrid>
class RankFunctor{
private:
	Method meth;
public:

	RankFunctor(Method m = Method()) : meth(m) {}

	template<class Blackbox>
	void operator() (unsigned long &res, Blackbox *B) const {
		LinBox::rank(res, *B, meth);
	}
};

/**********************************************************
 * API for rank computation                               *
 * rank is returned through a given unsigned long integer *
 **********************************************************/
void lb_rank(unsigned long &res, const BlackboxKey& key){
	RankFunctor<> fct;
	BlackboxFunction::call(res, key, fct);
}

/*****************************************************
 * API for rank computation                          *
 * rank is returned through an unsigned long integer *
 *****************************************************/
unsigned long lb_rank(const BlackboxKey& key){
	unsigned long r;
	lb_rank(r, key);
	return r;
}



#endif

// vim:sts=8:sw=8:ts=8:noet:sr:cino=>s,f0,{0,g0,(0,:0,t0,+0,=s
// Local Variables:
// mode: C++
// tab-width: 8
// indent-tabs-mode: nil
// c-basic-offset: 8
// End:

