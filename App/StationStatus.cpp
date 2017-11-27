#include "StationStatus.hpp"


StationStatus::StationStatus(const StationStatus &s)
{
   bikeAvailable = s.bikeAvailable;
   bikeSlots = s.bikeSlots;
   state = s.state;
}

StationStatus &StationStatus::operator =(const StationStatus &s)
{
   if (this != &s)
   {
      bikeAvailable = s.bikeAvailable;
      bikeSlots = s.bikeSlots;
      state = s.state;
   }

   return *this;
}
