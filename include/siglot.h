#ifndef _SIGLOT_H
#define _SIGLOT_H

namespace Siglot {
    
class ReceiverBase;

class SenderBase;

void run();

void connect(SenderBase* sender, ReceiverBase* receiver);

void disconnect(SenderBase* sender);

void disconnect(SenderBase* sender, ReceiverBase* receiver);

void disconnect(ReceiverBase* receiver);

template <class T>
void constRefSignal(SenderBase* sender, const T& data) {}

template <class T>
void valueSignal(SenderBase* sender, T data) {}

} // namespace Siglot

#endif
