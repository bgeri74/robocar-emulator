/**
 * @brief Justine - this is a rapid prototype for development of Robocar City Emulator
 *
 * @file myshmclient.cpp
 * @author  Norbert Bátfai <nbatfai@gmail.com>
 * @version 0.0.10
 *
 * @section LICENSE
 *
 * Copyright (C) 2014 Norbert Bátfai, batfai.norbert@inf.unideb.hu
 * Copyright (C) 2016, Gergő Bogacsovics, bgeri74@gmail.com
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
 * Robocar City Emulator and Robocar World Championship
 *
 * desc
 * 
 * 
 *
 */

#include <myshmclient.hpp>
//#include <trafficlexer.hpp>

char data[524288];

// Függvény a gangster ágensek lekérésére.
std::vector<justine::sampleclient::MyShmClient::Gangster> justine::sampleclient::MyShmClient::gangsters ( boost::asio::ip::tcp::socket & socket, int id,
    osmium::unsigned_object_id_type cop )
{

  boost::system::error_code err;

  size_t length = std::sprintf ( data, "<gangsters " );
  length += std::sprintf ( data+length, "%d>", id );

  socket.send ( boost::asio::buffer ( data, length ) );

  length = socket.read_some ( boost::asio::buffer ( data ), err );

  // Kivétel kezelés.
  if ( err == boost::asio::error::eof )
    {

      // TODO

    }
  else if ( err )
    {

      throw boost::system::system_error ( err );
    }

  /* A gangsterek adatait az alábbi változókban fogjuk tárolni.  */
  int idd {0};
  unsigned f, t, s;
  
  // Számlálók.
  int n {0};
  int nn {0};
  
  // A gangsterek vektora.
  std::vector<Gangster> gangsters;

  // Beolvassuk a gangsterek adatait.
  while ( std::sscanf ( data+nn, "<OK %d %u %u %u>%n", &idd, &f, &t, &s, &n ) == 4 )
    {
      nn += n;
      gangsters.push_back ( Gangster {idd, f, t, s} );
    }

  /*std::sort ( gangsters.begin(), gangsters.end(), [this, cop] ( Gangster x, Gangster y )
  {
    return dst ( cop, x.to ) < dst ( cop, y.to );
  } );*/

  std::cout.write ( data, length );
  std::cout << "Command GANGSTER sent." << std::endl;
  //std::this_thread::sleep_for ( std::chrono::milliseconds ( 20000 ) );

  return gangsters;
}

// Rendőrök inicializálása.
std::vector<justine::sampleclient::MyShmClient::Cop> justine::sampleclient::MyShmClient::initcops ( boost::asio::ip::tcp::socket & socket )
{

  boost::system::error_code err;

  size_t length = std::sprintf ( data, "<init guided %s 1 c>", m_teamname.c_str() );

  socket.send ( boost::asio::buffer ( data, length ) );

  length = socket.read_some ( boost::asio::buffer ( data ), err );


  // Kivételkezelés.
  if ( err == boost::asio::error::eof )
    {

      // TODO

    }
  else if ( err )
    {

      throw boost::system::system_error ( err );
    }

  /* A rendőrök főbb adatait ezekben fogjuk tárolni. */
  int idd {0};
  int f, t;
  char c;
  
  // Számlálók.
  int n {0};
  int nn {0};
  
  // A rendőrök vektora.
  std::vector<Cop> cops;

  // A rendőrök adatait egyesével kinyerjük.
  while ( std::sscanf ( data+nn, "<OK %d %d/%d %c>%n", &idd, &f, &t, &c, &n ) == 4 )
    {
      nn += n;
      cops.push_back ( idd );
    }

  std::cout.write ( data, length );
  std::cout << "Command INIT sent." << std::endl;

  return cops;
}


int justine::sampleclient::MyShmClient::init ( boost::asio::ip::tcp::socket & socket )
{

  boost::system::error_code err;

  size_t length = std::sprintf ( data, "<init guided %s 1 c>", m_teamname.c_str() );

  socket.send ( boost::asio::buffer ( data, length ) );

  length = socket.read_some ( boost::asio::buffer ( data ), err );

  if ( err == boost::asio::error::eof )
    {

      // TODO

    }
  else if ( err )
    {

      throw boost::system::system_error ( err );

    }

  int id {0};
  std::sscanf ( data, "<OK %d", &id );

  std::cout.write ( data, length );
  std::cout << "Command INIT sent." << std::endl;

  return id;

}

void justine::sampleclient::MyShmClient::pos ( boost::asio::ip::tcp::socket & socket, int id )
{

  boost::system::error_code err;

  size_t length = std::sprintf ( data, "<pos " );
  length += std::sprintf ( data+length, "%d %u %u>", id, 2969934868u, 651365957u );

  socket.send ( boost::asio::buffer ( data, length ) );

  length = socket.read_some ( boost::asio::buffer ( data ), err );

  if ( err == boost::asio::error::eof )
    {

      // TODO

    }
  else if ( err )
    {

      throw boost::system::system_error ( err );

    }

  std::cout.write ( data, length );
  std::cout << "Command POS sent." << std::endl;
}


void justine::sampleclient::MyShmClient::car ( boost::asio::ip::tcp::socket & socket, int id, unsigned *f, unsigned *t, unsigned* s )
{

  boost::system::error_code err;

  size_t length = std::sprintf ( data, "<car " );
  length += std::sprintf ( data+length, "%d>", id );

  socket.send ( boost::asio::buffer ( data, length ) );

  length = socket.read_some ( boost::asio::buffer ( data ), err );

  if ( err == boost::asio::error::eof )
    {

      // TODO

    }
  else if ( err )
    {

      throw boost::system::system_error ( err );
    }

  int idd {0};
  std::sscanf ( data, "<OK %d %u %u %u", &idd, f, t, s );

  std::cout.write ( data, length );
  std::cout << "Command CAR sent." << std::endl;

}

void justine::sampleclient::MyShmClient::route (
  boost::asio::ip::tcp::socket & socket,
  int id,
  std::vector<osmium::unsigned_object_id_type> & path
)
{

  boost::system::error_code err;

  size_t length = std::sprintf ( data,
                                 "<route %d %d", path.size(), id );

  for ( auto ui: path )
    length += std::sprintf ( data+length, " %u", ui );

  length += std::sprintf ( data+length, ">" );

  socket.send ( boost::asio::buffer ( data, length ) );

  length = socket.read_some ( boost::asio::buffer ( data ), err );

  if ( err == boost::asio::error::eof )
    {

      // TODO

    }
  else if ( err )
    {

      throw boost::system::system_error ( err );

    }

  std::cout.write ( data, length );
  std::cout << "Command ROUTE sent." << std::endl;

}

void justine::sampleclient::MyShmClient::start ( boost::asio::io_service& io_service, const char * port )
{

#ifdef DEBUG
  foo();
#endif

  boost::asio::ip::tcp::resolver resolver ( io_service );
  boost::asio::ip::tcp::resolver::query query ( boost::asio::ip::tcp::v4(), "localhost", port );
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve ( query );

  boost::asio::ip::tcp::socket socket ( io_service );
  boost::asio::connect ( socket, iterator );

  int id = init ( socket );

  pos ( socket, id );

  unsigned int g {0u};
  unsigned int f {0u};
  unsigned int t {0u};
  unsigned int s {0u};

  std::vector<Gangster> gngstrs;

  for ( ;; )
    {
      std::this_thread::sleep_for ( std::chrono::milliseconds ( 200 ) );

      car ( socket, id, &f, &t, &s );

      gngstrs = gangsters ( socket, id, t );

      if ( gngstrs.size() > 0 )
        g = gngstrs[0].to;
      else
        g = 0;
      if ( g > 0 )
        {

          std::vector<osmium::unsigned_object_id_type> path = hasDijkstraPath ( t, g );

          if ( path.size() > 1 )
            {

              std::copy ( path.begin(), path.end(),
                          std::ostream_iterator<osmium::unsigned_object_id_type> ( std::cout, " -> " ) );

              route ( socket, id, path );
            }
        }
    }
}

void justine::sampleclient::MyShmClient::start10 ( boost::asio::io_service& io_service, const char * port )
{

#ifdef DEBUG
  foo();
#endif

  boost::asio::ip::tcp::resolver resolver ( io_service );
  boost::asio::ip::tcp::resolver::query query ( boost::asio::ip::tcp::v4(), "localhost", port );
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve ( query );

  boost::asio::ip::tcp::socket socket ( io_service );
  boost::asio::connect ( socket, iterator );

  // Rendőrök vektora, amit be is állítunk rögtön.
  std::vector<Cop> cops = initcops ( socket );

  // A rendőrök adatait ezekben a változókban tároljuk.
  unsigned int g {0u}; // Ez jelzi majd, melyik gangstert szeretnénk üldözőbe venni.
  unsigned int f {0u};
  unsigned int t {0u};
  unsigned int s {0u};
  
  // Jelzi számunkra, hogy a rendőr ágensek száma nagyobb-e mint a gangster ágensek-é.
  // Ez azért fontos, mert 1 gangsterre 1 rendőrt állítunk, viszont ha van szabad rendőrünk, akkor azt fel szeretnénk használni.
  bool tooManyCops = false;

  // A gangsterek vektora.
  std::vector<Gangster> gngstrs;
 
  for ( ;; )
    {
	std::this_thread::sleep_for ( std::chrono::milliseconds ( 200 ) );
	
	//  Ha a gangsterek száma kevesebb mint a rendőrök száma, azt jelezzük.
	if(gngstrs.size() < cops.size()){
	  tooManyCops = true;
	}
	
	// Beállítjuk a ciklusszámlálót.
	int i = 0;
	
	//std::cout <<"Distances:\n";
	
	// Végigiterálunk a rendőrágenseken, és a legelőnyösebb rendőrt (ill. gangstert) bemozgatjuk a vektor adott helyére.
        //for ( std::vector<Cop>::iterator m = cops.begin(); m < cops.end(); m++ )
	for(auto cop:cops)
        {
	    
	    // Frissítjük a gngstrs vektorunkat.
	    gngstrs = gangsters ( socket, cops[0], t );
	    
	    //unsigned int gg {0u};
	    unsigned int ff {0u};
	    unsigned int tt {0u};
	    unsigned int ss {0u};
	    
	    unsigned long minDistance = std::numeric_limits<double>::max(); // Minden egyes körben beállítjuk a minimális távolságot.
	    
	    // A számunkra előnyös gangster ill. rendőr ágensek indexeit tároljuk ezekben.
	    int minGangIndex = i;
	    int minCopIndex = i;
		 
		  
	    //std::cout << "Distances: "<<std::endl;
	    
	    // Rendezési algoritmus kezdete.
	    for(int k = i, copSize = cops.size(); k < copSize; k++){
		    
		// Aktuális rendőr.
		auto copp = cops[k];
		// Kinyerjük a rendőr ágens adatait.
		car ( socket, copp, &ff, &tt, &ss );
			
		for(int j = i, gangSize = gngstrs.size(); j < gangSize; j++ ){
				
		    auto gangSta = gngstrs[j];
		    auto tempDistance = dst(tt, gangSta.to);
		    //std::cout<<"TempDistance: "<<tempDistance<<std::endl;
			      
		    // Ha az aktuális távolság kisebb, mint a minimumtávolság, beállítjuk az indexeket, és a távolságot.
		    if( tempDistance < minDistance){
			minDistance = tempDistance;
			minGangIndex = j;
			minCopIndex = k;
		    }
				      
		  }
		  
	      }
		  
		    
	      std::swap(gngstrs[i], gngstrs[minGangIndex]);
	      std::swap(cops[i], cops[minCopIndex]);
	      //std::cout<<"MinDistance: "<<minDistance<<std::endl;
	      
	      // Rendezési algoritmus vége
	    
	      // Lekérjük az adott rendőrágens főbb adatait, pl. pozícióját.
	      car ( socket, cop, &f, &t, &s );
	      
	      // Ha van gangster a szerveren, akkor beállítjuk az ágenseket, különben 0-val jelezzük az ellentétjét.
	      if ( gngstrs.size() > 0 )
		  if(i >= gngstrs.size()){
		    //std::cout<<"Setting COP#" <<i<<" to GANGSTER#" << i%gngstrs.size()<<std::endl;
		    g = gngstrs[i%gngstrs.size()].to;
		  }
		  else{
		    //std::cout<<"Setting COP#" <<i<<" to GANGSTER#" << i<<std::endl;
		    g = gngstrs[i].to;
		  }

	      else{
		g = 0;
		//std::cout << "COP NO." << i << "CANT CHASE ANYTHING"<<std::endl;
	      }
	      
	      //std::this_thread::sleep_for ( std::chrono::milliseconds ( 2000 ) );
	    
	      // Ha van gangster, akkor az adott rendőrkocsit el is inditjuk felé.
	      if ( g > 0 )
		{

		  std::vector<osmium::unsigned_object_id_type> path = hasDijkstraPath ( t, g );

		  if ( path.size() > 1 )
		    {

		      std::copy ( path.begin(), path.end(),
		      std::ostream_iterator<osmium::unsigned_object_id_type> ( std::cout, " -> " ) );

		      route ( socket, cop, path );
		    }
		}
	      
	      // Ciklusszámláló növelése.
	      i++;
        }
	
        
    }
}
