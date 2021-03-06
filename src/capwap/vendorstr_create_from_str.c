#include "bstr.h"
#include "format.h"


uint8_t * vendorstr_create_from_str(uint32_t vendor_id,const char *s)
{
	int l = strlen(s);
	if (s[0]!='.')
		return vendorstr_create(vendor_id,(uint8_t*)s,l);

	if (l<=2)
		return vendorstr_create(vendor_id,(uint8_t*)s,l);

	if (s[1]=='.')
		return vendorstr_create(vendor_id,(uint8_t*)s+1,l-1);

	if (s[1]!='x')
		return vendorstr_create(vendor_id,(uint8_t*)s,l);

	/* the string starts with ".x" - read hexbytes */
	l-=2;
	int msize=l/2;	
	if(l&1)
		msize++;


	uint8_t * mem = malloc(vendorstr_size(msize));
	if(!mem)
		return NULL;
	vendorstr_set_vendor_id(mem,vendor_id);
	vendorstr_set_len(mem,msize);

	cw_format_scan_hex_bytes(vendorstr_data(mem),s+2,l);
	return mem;		
}


