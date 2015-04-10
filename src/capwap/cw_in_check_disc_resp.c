
#include "capwap.h"
#include "capwap_items.h"
#include "intavltree.h"
#include "log.h"
#include "dbg.h"
#include "sock.h"

int cw_in_check_disc_resp(struct conn *conn, struct cw_action_in *a, uint8_t * data,
			 int len)
{
	cw_action_in_t *mlist[20];
	int n = cw_check_missing_mand(mlist, conn, a);
	cw_dbg_missing_mand(DBG_ELEM, conn, mlist, n, a);

	cw_dbg(DBG_CW_INFO,"This response came from: %s\n",sock_addr2str(&conn->addr));


	/* if mandatory elements are missing, ignore this response */
	if (n) {
		cw_dbg(DBG_CW_INFO,
		       "Ignoring Discovery Response from %s - missing mandatory elements.",
		       sock_addr2str(&conn->addr));
		return -1;
	}

	/*  we have all AC information in the incomming buffer */
	cw_itemstore_t discs;

	discs = cw_itemstore_get_avltree_c(conn->remote, CW_ITEM_DISCOVERIES,
					   cw_itemstore_create);

	if ( !discs ) {
		cw_log(LOG_ERR,"Can't allocate store for disc resp");
		return 0;
	}

	cw_itemstore_set_avltree(discs,discs->count,conn->incomming);
	conn->incomming = cw_itemstore_create();


	return 0;
}
