#ifndef PTRMACRO_H
#define PTRMACRO_H

#ifndef STDTYPES_H
	#include "stdtypes.h"
#endif


/* returns syntax reference to a field within a given struct name;
 * useful for sizeof(MEMBER(s,f)) or sizeof(*MEMBER(s,f)) */

#define MEMBER(struc,field) \
	((struc*)NULL)->field

/* returns offset of field within a given struct name,
 * and field name ie: OFFSET(struct sname,fieldname) */

#define OFFSET(struc,field) \
	(USHORT)((ULONG)((PTR)&MEMBER(struc,field)-(PTR)NULL))

/* offset to first byte after a field */

#define POSTOSET(struc,field) \
	(OFFSET(struc,field)+sizeof(MEMBER(struc,field)))

/* macro for defining pad sizes in structures can not define a pad of 
 * less than two bytes  one may use pname for the offset to it but
 * sizeof(struc->pname) will not be valid 
 *
 *	struct sname {
 *		char fld1[64];
 *		PADTO(68,sname,pname);
 *	};
 * will make:
 *
 *	struct sname {
 *		char fld1[64];
 *		UBYTE pname[1];
 *		UBYTE __pname[3];
 *	};
 */


#define PADTO(sz,struc,padfld) \
	UBYTE padfld[1];UBYTE __##padfld[(sz)-OFFSET(struct struc,padfld)-1]

/* returns pointer to structure given struct name, field name, and
 * pointer to field */

#define TOSTRUCT(struc,field,fieldptr) \
	((struc*)((PTR)(fieldptr)-OFFSET(struc,field)))

/* gives size of memory given pointer to start and one byte beyond end */

#define SIZE(beg,end)    (unsigned)((PTR)(end)-(PTR)(beg))

/* gives offset to array element 1 or what ptr + 1 will increment you to */

#define PADSIZE(struc) SIZE(NULL,&((struc*)NULL)[1])

/* adds "offset" byte size to "base" pointer */

#define OPTR(base,offset) ((void*)((PTR)(base)+(offset))) 

/* far optr would have a pt_to_long and a long_to_pt() in it for 286 stuff */
#define FOPTR(base,offset) OPTR(base,offset)

#ifdef SLUFFED
	#define FOPTR(base,offset) long_to_pt(pt_to_long(base)+(offset))
#endif

#define Array_els(arr) (sizeof(arr)/sizeof(arr[0]))

#define strempty(s) ((s)[0] == 0)

/* macro to assign something to what a void pointer points to. */
#define vass(v,type) (*((type *)(v)))

/* used to put or get values into (or from) a void pointer 
   and increment the pointer by the size of what's pointed to 
   NOTE use of comma operator in VPUTVAL */


#define VPUTVAL(pt,typ,val) (*((typ*)pt)=(val),(pt)=OPTR(pt,sizeof(typ)));
#define VGETVAL(pt,typ) *((typ*)pt);(pt)=OPTR(pt,sizeof(typ)) 

#endif /* PTRMACRO_H */

