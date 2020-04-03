#ifndef PLUGIN_HPP
#define PLUGIN_HPP

namespace plugio::plugin
{

// forward declaration
class Plugin;

// the types of the class factories                                          
typedef Plugin* createPluginFn();                                                 
typedef void destroyPluginFn(Plugin*);

// signals
typedef bool readInSignalBFn(void *, int, bool);
typedef void setReadInSignalBFn(readSignalBFn);
typedef bool readInSignalNFn(void *, int, double);
typedef void setReadInSignalNFn(readSignalNFn);
typedef bool readInSignalSFn(void *, int, const char *);
typedef void setReadInSignalSFn(readSignalSFn);

typedef bool writeOutSignalBFn(void *, int, bool);
typedef void setwriteOutSignalBFn(writeOutSignalBFn);
typedef bool writeOutSignalNFn(void *, int, double);
typedef void setwriteOutSignalNFn(writeOutSignalNFn);
typedef bool writeOutSignalSFn(void *, int, const char *);
typedef void setwriteOutSignalSFn(writeOutSignalSFn);

typedef void onInBChangeFn(void *, int, bool);
typedef void onInBChangeFn(void *, int, double);
typedef void onInBChangeFn(void *, int, const char *);

class Plugin
{
public:
    Plugin();
    virtual ~Plugin();

    static readInSignalBFn readInSignalB;
    static readInSignalNFn readInSignalN;
    static readInSignalSFn readInSignalS;
    static writeOutSignalBFn writeOutSignalB;
    static writeOutSignalNFn writeOutSignalN;
    static writeOutSignalSFn writeOutSignalS;

private:

};

}

#endif // PLUGIN_HPP
