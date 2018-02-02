#include <iostream>
#include "type_helpers.h"

class AClassWhatNeedsToDemangleName
{
};

class YetAnotherClassWNTDName : public AClassWhatNeedsToDemangleName
{
};

int main()
{
  AClassWhatNeedsToDemangleName val1;
  YetAnotherClassWNTDName val2;
  AClassWhatNeedsToDemangleName * p_val2 = &val2;
  std::cout
    << "fst: " << type_helpers::type_name<typeof(val1)>() << "\n"
    << "snd: " << type_helpers::type_name<typeof(val2)>() << "\n"
    << "ptr: " << type_helpers::type_name<typeof(p_val2)>() << std::endl;
}
