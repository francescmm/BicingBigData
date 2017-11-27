#ifndef STATIONSTATUS_HPP
#define STATIONSTATUS_HPP

enum class StationState { OPEN, CLOSED };

class StationStatus
{
   public:
      StationStatus() { }
      StationStatus(const StationStatus &s);
      StationStatus & operator = (const StationStatus &s);
      ~StationStatus() { }

   private:
      int bikeSlots = 0;
      int bikeAvailable = 0;
      StationState state = StationState::OPEN;
};

#endif // STATIONSTATUS_HPP
