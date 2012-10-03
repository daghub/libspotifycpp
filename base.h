#ifndef BASE_H
#define BASE_H

#include <boost/utility.hpp>
#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/exception/all.hpp>
#include <libspotify/api.h>

#define NS_SPOTIFY_BEGIN namespace spotify {
#define NS_SPOTIFY_END }

NS_SPOTIFY_BEGIN

struct error : virtual boost::exception , virtual std::exception {};
typedef boost::error_info< struct tag_sp_error, sp_error > sp_error_info;
typedef boost::error_info< struct tag_call, std::string > sp_call_info;

#define CHK(x) \
  { sp_error res = x; if (res != SP_ERROR_OK) BOOST_THROW_EXCEPTION(error() << sp_error_info(res) << sp_call_info(#x)); }
#define CHK_NULL(x) \
  { if (!(x)) BOOST_THROW_EXCEPTION(error() << sp_call_info(#x)); }

namespace sig = boost::signals2;

class search;
class artist;

typedef boost::shared_ptr< search > search_ptr;
typedef boost::shared_ptr< artist > artist_ptr;

NS_SPOTIFY_END


#endif BASE_H
