#ifndef MAPCTRL_HPP
#define MAPCTRL_HPP

#include <vector>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include "viewport.hpp"
#include "point.hpp"
#include "osmlayer.hpp"
#include "gpxlayer.hpp"
#include "gpsdlayer.hpp"
#include "gfx.hpp"

class mapctrl : public Fl_Widget, public event_listener, public event_generator
{
    public:
        mapctrl(int x, int y, int w, int h, const char *label);
        ~mapctrl();

        // FLTK event handling routine
        int handle(int event);

        // Basemap configuration
        void basemap(
                const std::string& name, 
                const std::string& url, 
                unsigned int zmin, 
                unsigned int zmax, 
                unsigned int parallel,
                int imgtype);

        // GPSd configuration
        bool gpsd_connected();
        void gpsd_connect(const std::string& host, const std::string& port);
        void gpsd_disconnect();
        void gpsd_lock(bool start);
        void gpsd_record(bool start);
        int gpsd_mode();

        // GPX configuration
        void gpx_loadtrack(const std::string& path);
        void gpx_savetrack(const std::string& path);
        void gpx_cleartrack();
        bool gpx_wpselected();
        void gpx_wpdelete();
        double gpx_wpelevation();
        void gpx_wpelevation(double e);
        point2d<double> gpx_wppos();
        void gpx_wppos(const point2d<double>& p);
        double gpx_trip();
        
        // Viewport control
        unsigned int zoom();
        void zoom(unsigned int z);
        void goto_cursor();
        point2d<double> mousepos();
        
        // Event classes
        class event_notify;
    private:
        // Pixel delta for keyborad map motion commands
        static const int PXMOTION = 15;

        // Utility methods
        void refresh();

        // Widget event handling routines
        int handle_move(int event);
        int handle_enter(int event);
        int handle_leave(int event);
        int handle_push(int event);
        int handle_release(int event);
        int handle_drag(int event);
        int handle_mousewheel(int event);
        int handle_keyboard(int event);
        point2d<int> vp_relative(const point2d<int>& pos);
        bool vp_inside(const point2d<int>& pos);

        // GPSd-layer event handlers
        bool gpsd_evt_motion(const gpsdlayer::event_motion *e);
        bool gpsd_evt_status(const gpsdlayer::event_status *e);

        // Basemap-layer event handlers
        bool osm_evt_notify(const osmlayer::event_notify *e);

        // GPX-layer event handlers
        bool gpx_evt_notify(const gpxlayer::event_notify *e);

        // Layers
        osmlayer *m_basemap;
        gpxlayer *m_gpxlayer;
        gpsdlayer *m_gpsdlayer;

        point2d<int> m_mousepos;
        viewport m_viewport;
        canvas m_offscreen;
        bool m_lockcursor;
        bool m_recordtrack;

    protected:
        void draw();
};

class mapctrl::event_notify : public event_base
{
    public:
        event_notify() {};
        ~event_notify() {};
};

#endif // MAPCTRL_HPP

