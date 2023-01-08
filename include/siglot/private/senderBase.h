#ifndef _SIGLOT_SENDER_BASE_H
#define _SIGLOT_SENDER_BASE_H

namespace Siglot {

/** Forward declarations */
class ReceiverBase;

/** Base class for all the senders */
class SenderBase {

public:
    /** Performs a connection to the receiver
     *  
     * \param receiver receiver to connect to
     */
    void connectTo(ReceiverBase* receiver);

    /** Performs a disconnection from the receiver
     *  
     * \param receiver receiver to disconnect from
     */
    void disconnectFrom(ReceiverBase* receiver);
    
    /** Disconnect from all connected receivers */
    void disconnectFromAll() ;

    /** Destructor */
    virtual ~SenderBase();
};

} // namespace Siglot

#endif // _SIGLOT_SENDER_BASE_H
