
/*  
 *  $Id$
 *
 *                              
 *                    L O S  A L A M O S
 *              Los Alamos National Laboratory
 *               Los Alamos, New Mexico 87545
 *                                  
 *  Copyright, 1986, The Regents of the University of California.
 *                                  
 *           
 *	Author Jeffrey O. Hill
 *	johill@lanl.gov
 */

#include "iocinf.h"
#include "comBuf_IL.h"

bool comBuf::flushToWire ( wireSendAdapter &wire )
{
    unsigned occupied = this->occupiedBytes ();
    while ( occupied ) {
        unsigned nBytes = wire.sendBytes ( &this->buf[this->nextReadIndex], 
                occupied );
        if ( nBytes == 0u ) {
            this->nextReadIndex = this->nextWriteIndex;
            return false;
        }
        this->nextReadIndex += nBytes;
        occupied = this->occupiedBytes ();
    }
    return true;
}