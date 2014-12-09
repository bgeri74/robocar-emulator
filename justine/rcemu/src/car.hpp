#ifndef ROBOCAR_CAR_HPP
#define ROBOCAR_CAR_HPP

/**
 * @brief Justine - this is a rapid prototype for development of Robocar City Emulator
 *
 * @file car.hpp
 * @author  Norbert Bátfai <nbatfai@gmail.com>
 * @version 0.0.10
 *
 * @section LICENSE
 *
 * Copyright (C) 2014 Norbert Bátfai, batfai.norbert@inf.unideb.hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 * GNU Robocar City Emulator and Robocar World Championship
 *
 * desc
 *
 */

#include <osmium/osm/types.hpp>
#include <iostream>
#include <vector>

namespace justine {
namespace robocar {

enum class CarType: unsigned int {
     NORMAL=0, POLICE, GANGSTER, CAUGHT
};

class Traffic;

class Car {
public:

     Car ( Traffic & traffic , CarType type = CarType::NORMAL );

     virtual void init();

     virtual void step();

     osmium::unsigned_object_id_type from() const {
          return m_from;
     }
     osmium::unsigned_object_id_type to() const {
          return m_to;
     }
     osmium::unsigned_object_id_type get_step() const {
          return m_step;
     }
     CarType get_type() const {
          return m_type;
     }
     void set_type ( CarType type ) {
          m_type = type;
     }
     
     osmium::unsigned_object_id_type to_node() const;
     osmium::unsigned_object_id_type get_max_steps() const;
     virtual void nextEdge ( void );
     virtual void nextSmarterEdge ( void );

     friend std::ostream & operator<< ( std::ostream & os, Car & c ) {

          std::cout
                    << c.m_from
                    << " "
                    << c.to_node()
                    << " "
                    << c.get_max_steps()
                    << " "
                    << c.get_step()
                    << " "
                    << static_cast<unsigned int> ( c.get_type() );

          return os;

     }

protected:
     Traffic & traffic;
     CarType m_type {CarType::NORMAL};
     osmium::unsigned_object_id_type m_from {3130863972};
     osmium::unsigned_object_id_type m_to {0};
     osmium::unsigned_object_id_type m_step {0};

private:

};

class SmartCar : public Car {
public:
     SmartCar ( Traffic & traffic, CarType type, bool guided );

     virtual void step();
     virtual void init();

     bool get_guided() const {
          return m_guided;
     }
     void set_route ( std::vector<unsigned int> & route );
     virtual void nextEdge ( void );
     virtual void nextGuidedEdge ( void );
     bool set_fromto ( unsigned int from, unsigned int to );

private:
     bool m_guided {false};
     bool m_routed {false};

     std::vector<unsigned int> route;

};

class CopCar : public SmartCar {
public:
  CopCar ( Traffic & traffic, bool guided );
  
  int get_num_captured_gangsters() const {
    return m_num_captured_gangsters;
  }
  
protected:
  
  int m_num_captured_gangsters{0};
  
};

}
} // justine::robocar::


#endif // ROBOCAR_CAR_HPP

