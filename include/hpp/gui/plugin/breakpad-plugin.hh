#ifndef HPP_GUI_PLUGIN_BREAKPAD_PLUGIN_HH
#define HPP_GUI_PLUGIN_BREAKPAD_PLUGIN_HH

#include <client/linux/handler/exception_handler.h>
#include <hpp/gui/plugin-interface.hh>

class BreakPadPlugin : public QObject, public hpp::gui::PluginInterface
{
  Q_OBJECT
  Q_INTERFACES (hpp::gui::PluginInterface)

public:
  explicit BreakPadPlugin ();

  virtual ~BreakPadPlugin ();

  static bool dumpCallback( const google_breakpad::MinidumpDescriptor& descriptor,
      void* context, bool succeeded);

  // PluginInterface interface
public:
  void init();
  QString name() const;

private:
  google_breakpad::ExceptionHandler *eh;
};

#endif // HPP_GUI_PLUGIN_BREAKPAD_PLUGIN_HH
