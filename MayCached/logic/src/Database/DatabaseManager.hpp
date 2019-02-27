#ifndef DATABASE_MANAGER
#define DATABASE_MANAGER
#include "Database/IDatabaseManager.hpp"
namespace maycached {
namespace logic {
class DatabaseManager: public IStorageManager
{
/*public:
    DatabaseManager();
    std::fstream serializeToFile(const IStorage&) const override;
    std::unique_ptr<IStorage> restoreFromFile(std::fstream&& fs)  const override;
private:*/
};


} }
#endif //I_DATABASE_MARSHALLER
