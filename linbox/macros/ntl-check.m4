# Check for NTL
# Bradford Hovinen, 2001-06-13
# Inspired by gnome-bonobo-check.m4 by Miguel de Icaza, 99-04-12
# Stolen from Chris Lahey       99-2-5
# stolen from Manish Singh again
# stolen back from Frank Belew
# stolen from Manish Singh
# Shamelessly stolen from Owen Taylor

dnl LB_CHECK_NTL ([MINIMUM-VERSION [, ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
dnl
dnl Test for Victor Shoup's NTL (Number Theory Library) and define
dnl NTL_CFLAGS and NTL_LIBS

AC_DEFUN([LB_CHECK_NTL],
[

AC_ARG_WITH(ntl-prefix,[  --with-ntl-prefix=PFX   Prefix where NTL is installed (optional)],
[ntl_prefix="$withval"],[ntl_prefix=""])

min_ntl_version=ifelse([$1], ,5.0,$1)
AC_MSG_CHECKING(for NTL >= $min_ntl_version)

if test x$ntl_prefix = x; then
	ntl_prefix=/usr/local
else 
	LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${ntl_prefix}/lib"
	export LD_LIBRARY_PATH
fi

dnl Check for existence

if test "x${ntl_prefix}" != "x/usr" -a "x${ntl_prefix}" != "x/usr/local"; then
	NTL_CFLAGS="-I${ntl_prefix}/include"
	NTL_LIBS="-L${ntl_prefix}/lib -lntl"
else
	NTL_CFLAGS=
	NTL_LIBS=-lntl
fi

BACKUP_CXXFLAGS=${CXXFLAGS}
BACKUP_LIBS=${LIBS}

CXXFLAGS="${CXXFLAGS} ${NTL_CFLAGS} ${GMP_CFLAGS}"
LIBS="${LIBS} ${NTL_LIBS} ${GMP_LIBS}"

AC_TRY_LINK(
[#include <NTL/ZZ.h>],
[NTL::ZZ a;],
[
AC_TRY_RUN(
[#include <NTL/version.h>
int main () { if (NTL_MAJOR_VERSION < 5) return -1; else return 0; }
],[
AC_MSG_RESULT(found)
AC_SUBST(NTL_CFLAGS)
AC_SUBST(NTL_LIBS)
AC_DEFINE(HAVE_NTL,1,[Define if NTL is installed])

# NTL was found, so make sure tests and headers get included.

HAVE_NTL=yes

ifelse([$2], , :, [$2])
],[
AC_MSG_RESULT(not found)
echo "Sorry, your NTL version is too old. Disabling."

unset NTL_CFLAGS
unset NTL_LIBS

ifelse([$3], , :, [$3])
],[
AC_MSG_RESULT(unknown)
echo "WARNING: You appear to be cross compiling, so there is no way to determine"
echo "whether your NTL version is new enough. I am assuming it is."

HAVE_NTL=yes

AC_SUBST(NTL_CFLAGS)
AC_SUBST(NTL_LIBS)
AC_DEFINE(HAVE_NTL,1,[Define is NTL is installed])

ifelse([$2], , :, [$2])
])
],
[
AC_MSG_RESULT(not found)

if test x$ntl_prefix != x/usr/local; then
	AC_MSG_WARN(NTL >= 5.0 was not found. Please double-check the directory you gave.  LinBox also requires the NTL namespace to be enabled.  Please make sure NTL is compiled correctly.)
fi

unset NTL_CFLAGS
unset NTL_LIBS

ifelse([$3], , :, [$3])
])

AM_CONDITIONAL(HAVE_NTL, test "x$HAVE_NTL" = "xyes")

CXXFLAGS=${BACKUP_CXXFLAGS}
LIBS=${BACKUP_LIBS}

])
