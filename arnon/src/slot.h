/// ArnonSidescroller

#ifndef SLOT_H
#define SLOT_H

#include "delegate.h"

template<typename Signature>
class Slot final
{
private:
    // The delegate of the slot
    fastdelegate::FastDelegate<Signature> m_delegate;

    // The type of this object
    using SlotType = Slot<Signature>;
    
public:
    // Create slot without a delegate
    Slot() = default;

    // Construct slot from a regular or static member function
    Slot(Signature function) : m_delegate(function) {}
    
    // Construct slot from a member function
    template<typename ClassInstance, typename MemberFunctionPtr>
    Slot(ClassInstance* object, MemberFunctionPtr function) : m_delegate(object, function) {}

    // Call the slot with Args
    template<typename... Args>
    auto operator()(Args&&... args) const { return m_delegate(std::forward<Args>(args)...); }

    // Comparison Operators
    friend bool operator==(const SlotType& lhs, const SlotType& rhs) { return   lhs.m_delegate  == rhs.m_delegate ;}
    friend bool operator!=(const SlotType& lhs, const SlotType& rhs) { return !(lhs.m_delegate  == rhs.m_delegate);}
    friend bool operator<(const SlotType& lhs, const SlotType& rhs)  { return   lhs.m_delegate  <  rhs.m_delegate ;}
    friend bool operator<=(const SlotType& lhs, const SlotType& rhs) { return !(lhs.m_delegate  >  rhs.m_delegate);}
    friend bool operator>(const SlotType& lhs, const SlotType& rhs)  { return   lhs.m_delegate  >  rhs.m_delegate ;}
    friend bool operator>=(const SlotType& lhs, const SlotType& rhs) { return !(lhs.m_delegate  <  rhs.m_delegate);}

};

#endif // SLOT_H
