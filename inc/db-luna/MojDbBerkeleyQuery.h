/* @@@LICENSE
*
*      Copyright (c) 2009-2012 Hewlett-Packard Development Company, L.P.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* LICENSE@@@ */


#ifndef MOJDBBERKELEYQUERY_H_
#define MOJDBBERKELEYQUERY_H_

#include "db/MojDbDefs.h"
#include "db-luna/MojDbBerkeleyEngine.h"
#include "db/MojDbIsamQuery.h"

class MojDbBerkeleyQuery : public MojDbIsamQuery
{
public:
	MojDbBerkeleyQuery();
	~MojDbBerkeleyQuery();

	MojErr open(MojDbBerkeleyDatabase* db, MojDbBerkeleyDatabase* joinDb,
			MojAutoPtr<MojDbQueryPlan> plan, MojDbStorageTxn* txn);
	MojErr getById(const MojObject& id, MojDbStorageItem*& itemOut, bool& foundOut);

	virtual MojErr close();

private:
	static const guint32 OpenFlags;
	static const guint32 SeekFlags;
	static const guint32 SeekIdFlags;
	static const guint32 SeekEmptyFlags[2];
	static const guint32 NextFlags[2];

	virtual MojErr seekImpl(const ByteVec& key, bool desc, bool& foundOut);
	virtual MojErr next(bool& foundOut);
	virtual MojErr getVal(MojDbStorageItem*& itemOut, bool& foundOut);
	MojErr getKey(bool& foundOut, guint32 flags);

	MojDbBerkeleyCursor m_cursor;
	MojDbBerkeleyItem m_key;
	MojDbBerkeleyItem m_val;
	MojDbBerkeleyItem m_primaryVal;
	MojDbBerkeleyDatabase* m_db;
};

#endif /* MOJDBBERKELEYQUERY_H_ */
