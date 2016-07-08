#pragma once


#include "engine/resource.h"
#include "engine/resource_manager.h"
#include "engine/resource_manager_base.h"


namespace Lumix
{


struct PrefabResource : public Resource
{
	PrefabResource(const Path& path, ResourceManager& resource_manager, IAllocator& allocator)
		: Resource(path, resource_manager, allocator)
		, blob(allocator)
	{
	}


	void unload(void) override { blob.clear(); }


	bool load(FS::IFile& file) override
	{
		file.getContents(blob);
		return true;
	}


	Lumix::OutputBlob blob;
};


class PrefabResourceManager : public ResourceManagerBase
{
public:
	PrefabResourceManager(IAllocator& allocator)
		: m_allocator(allocator)
		, ResourceManagerBase(allocator)
	{
	}


protected:
	Resource* createResource(const Path& path) override
	{
		return LUMIX_NEW(m_allocator, PrefabResource)(path, getOwner(), m_allocator);
	}


	void destroyResource(Resource& resource) override
	{
		return LUMIX_DELETE(m_allocator, &static_cast<PrefabResource&>(resource));
	}


private:
	IAllocator& m_allocator;
};


} // namespace Lumix