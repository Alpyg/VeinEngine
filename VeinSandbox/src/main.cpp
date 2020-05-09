#include <VeinEngine.h>

using namespace Vein;

int main()
{
    VN_INFO("{0}", "INFO");
    VN_WARN("{0}", "WARN");
    VN_TRACE("{0}", "TRACE");
    VN_ERROR("{0}", "ERROR");
    VN_FATAL("{0}", "FATAL");

    return 0;
}