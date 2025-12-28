#ifndef __DEBUG_ONLY_HEADER__
#define __DEBUG_ONLY_HEADER__

#ifdef _DEBUG
	#define IN_DEBUG(x) x
#else
	#define IN_DEBUG(x)
#endif

#endif