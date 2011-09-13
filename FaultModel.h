#ifndef FAULTMODEL_H
#define FAULTMODEL_H

class FaultModelBase
{
};

template <class T>
class FaultModel : public FaultModelBase
{
   public:

      // Returns a faulty reading of value
      virtual T GetFaulty(const T value) = 0;

      // Makes the specified value faulty (i.e. in-place GetFaulty)
      void MakeFaulty(T &value) { value = GetFaulty(value); }
};

#endif
