// TerraLib
#include "TeConnectionPool.h"
#include "TeDatabase.h"
#include "TeDatabaseFactory.h"
#include "TeDatabaseFactoryParams.h"

TeConnectionPool::TeConnectionPool(const unsigned int& nConns, const clock_t& timeOut) :
nConns_(nConns),
ticket_(0),
timeOut_(timeOut)
{}

TeConnectionPool::~TeConnectionPool()
{
   clear();
}

bool TeConnectionPool::initialize(const std::string& user, const std::string& password, const std::string& host, 
                                  const std::string& dbName, const std::string& dbmsName, const int& portNumber)
{
    // Clear the pool
    //clear();

    if(!databases_.empty())
        return true;

    // Builds the database params
    TeDatabaseFactoryParams params;
    params.user_ = user;
    params.password_ = password;
    params.host_ = host;
    params.database_ = dbName;
	params.dbms_name_ = dbmsName;
	params.port_ = portNumber;
    
    // Try connect to the informed database
    TeDatabase* db = TeDatabaseFactory::make(params);
    if(db == 0 || !db->isConnected())
        return false;
    databases_.push_back(db);
    freeConns_.insert(0);

    // Create the set of databases
    for(unsigned int i = 1; i < nConns_; ++i)
    {
        TeDatabase* db = TeDatabaseFactory::make(params);
        databases_.push_back(db);
        freeConns_.insert(i);
    }

    return true;
}

TeConnection* TeConnectionPool::getConnection()
{
    mutexLock_.lock();

    if(freeConns_.empty())
    {
        // There are not free connections!

        // Gets a tickets and...
        unsigned int myTicket = getTicket();
        // ... wait on the queue
        requestQueue_.push_back(myTicket);

        mutexLock_.unLock();

        clock_t start = clock();
        while(clock() - start < timeOut_) // Start counting...
        {
            mutexLock_.lock();
            if(!freeConns_.empty()) // Are there free connections?
            {
                if(myTicket == requestQueue_[0]) // Is it me?
                {
                    // Yeah!
                    TeConnection* c = getFreeConnection();
                    freeTickets_.insert(myTicket); // Give back the ticket and... 
                    requestQueue_.erase(requestQueue_.begin()); // ... get off the queue!
                    mutexLock_.unLock();
                    return c;
                }
            }
            mutexLock_.unLock();

            // waiting...
            #ifdef WIN32    
                Sleep(100);
            #else
                sleep(100);
            #endif
        }

        // Time out exceeded!
        mutexLock_.lock();
        for(unsigned int i = 0; i < requestQueue_.size(); ++i)
        {
            if(requestQueue_[i] == myTicket)
            {
                requestQueue_.erase(requestQueue_.begin() + i);  // Get off (angry?!) the queue...
                break;
            }
        }
        freeTickets_.insert(myTicket); // Give back the ticket and... go home... =/
        mutexLock_.unLock();
        
        return 0;
    }

    TeConnection* c = getFreeConnection();

    mutexLock_.unLock();
    
    return c;
}

void TeConnectionPool::releaseConnection(TeConnection* conn)
{
    mutexLock_.lock();

    unsigned int id = conn->getId();

    freeConns_.insert(id);

    delete conn;

    mutexLock_.unLock();
}

void TeConnectionPool::setTimeOut(const clock_t t)
{
    timeOut_ = t;
}

TeConnection* TeConnectionPool::getFreeConnection()
{
    unsigned int id = *freeConns_.begin();
    freeConns_.erase(freeConns_.begin());

    TeDatabase* db = databases_[id];
    TeConnection* c = db->getConnection();
    c->setId(id);
    
    return c;
}

unsigned int TeConnectionPool::getTicket()
{
    if(freeTickets_.empty())
        return ++ticket_;

    unsigned int t = *freeTickets_.begin();
    freeTickets_.erase(freeTickets_.begin());

    return t;
}

void TeConnectionPool::clear()
{
    for(unsigned int i = 0; i < databases_.size(); ++i)
        delete databases_[i];

    databases_.clear();
    freeConns_.clear();
    requestQueue_.clear();

    ticket_ = 0;
    freeTickets_.clear();
}
