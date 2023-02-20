#ifndef _SIGLOT_H
#define _SIGLOT_H

#include "siglot/private/siglotCore.h"

namespace Siglot {
    
/** Forward declarations*/
class ReceiverBase;
class SenderBase;

/** Start the loop of receiveing and sending signals */
void run();

/** Process next signal
 * 
 * \return true if signal was prcessed, false if queue was empty
 */
bool processNextSignal();

/** Connect one sender to the one receiver
 * 
 *  Each time sender emit signal, the receiver's slot will be called
 * 
 * \param sender object that will send a signal
 * \param receiver object that will call the slot
 */
void connect(SenderBase* sender, ReceiverBase* receiver);

/** Disconnect one sender from one receiver
 * 
 * \param sender object that will be disconnected from receiver
 * \param receiver object that will be disconnected from sender
 */
void disconnect(SenderBase* sender, ReceiverBase* receiver);

/** Disconnect sender from all it's receivers
 * 
 * \param sender object that will be disconnected from active receivers
 */
void disconnect(SenderBase* sender);

/** Disconnect receiver from all senders
 * 
 * \param receiver object that will be disconnected from active senders
 */
void disconnect(ReceiverBase* receiver);

/** Perform a signal from the sender with const reference to the data
 * 
 *  WARNING: User must ensure that reference is valid when slot is called!
 * 
 * \param sender object that preforms send a signal
 * \param data const reference data to send with the signal
 */
template <class T>
void constRefSignal(SenderBase* sender, const T& data) {
    SiglotCore::get()->addConstRefCallback<T>(reinterpret_cast<std::uintptr_t>(sender), data);
}

/** Perform a signal from the sender with data
 * 
 * The data will be copied only if more that one receiver is connected
 * to the sender.
 * 
 * \param sender object that preforms send a signal
 * \param data data to send with the signal
 */
template <class T>
void valueSignal(SenderBase* sender, T data) {
    SiglotCore::get()->addValueCallback<T>(reinterpret_cast<std::uintptr_t>(sender), std::move(data));
}

} // namespace Siglot

#endif // _SIGLOT_H
