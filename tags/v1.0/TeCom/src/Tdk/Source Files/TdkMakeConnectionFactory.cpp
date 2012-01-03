#include <TdkMakeConnectionFactory.h>
#include <TeAdoDB.h>
#include <TeAdoOracle.h>
#include <TeAdoSqlServer.h>
#include <TePostgreSQL.h>
#include <TeAdoFireBird.h>


using namespace TDK_Connection;

TeDatabase * TdkMakeConnectionFactory::build(const TDK_Connection::connType &type,VARIANT conn)
{
	TeDatabase *db=0;
	switch(type)
		{
			case SqlServer:
				{
					db=new TeSqlServer();
					((TeSqlServer*)db)->connection(conn.pdispVal);
				} break;
			case Oracle:
				{
					db=new TeOracle();
					((TeOracle*)db)->connection(conn.pdispVal);
				}break;
			case FireBird:
				{
					db=new TeFireBird();
					((TeFireBird*)db)->connection(conn.pdispVal);
					
				}break;
			case PostgreSQL:
				{
					db = new TePostgreSQL(true);
					((TePostgreSQL*)db)->connect((PGconn*)conn.ullVal);
				}break;
			default://conexao acces eh a default
				{
					db=new TeAdo();
					((TeAdo*)db)->connection(conn.pdispVal);
				}
		}
	return db;
}

TeDatabase* TdkMakeConnectionFactory::build(const TDK_Connection::connType &type,const std::string &databaseName, const std::string &user,const std::string &password, const std::string &host, const std::string &port)
{
	int	iPort=-1;
	TeDatabase *db=0;
	switch(type)
		{
			case SqlServer:
				{
					db=new TeSqlServer();
				} break;
			case Oracle:
				{
					db=new TeOracle();
				}break;
			case FireBird:
				{
					db=new TeFireBird();
					
				}break;
			case PostgreSQL:
				{
					db = new TePostgreSQL();
				}break;
			default://conexao acces eh a default
				{
					db=new TeAdo();
				}
		}
	if(db)
	{
		if(!port.empty()) iPort=atoi(port.c_str());
		if(db->connect(host,user,password,databaseName,iPort) == false)
		{
			delete db;
			db=NULL;
		}
	}
	return db;


}