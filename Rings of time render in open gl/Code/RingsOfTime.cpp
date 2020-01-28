#include "RingsOfTime.hpp"
#include "MyUtils.hpp"
#include <tyga/ActorWorld.hpp>
#include <tyga/GraphicsCentre.hpp>
#include <tyga/Actor.hpp>
#include <tyga/BasicWorldClock.hpp>
#include <tyga/Math.hpp>

void RingsOfTime::
actorDidEnterWorld(std::shared_ptr<tyga::Actor> root_actor)
{
	auto world = tyga::ActorWorld::defaultWorld();
	auto graphics = tyga::GraphicsCentre::defaultCentre();

	/*
	 * Tutorial: This section of code creates the base's mesh, material
	 *           and model.  It doesn't need modifying.  Use it as an example
	 *           when creating the other shapes.
	 */
	 /////////////////////////////////////////////////////////////////////////
	 //base (creats the mesh for te actor base )
	auto base_material = graphics->newMaterial();
	base_material->colour = tyga::Vector3(1.f, 0.2f, 0.2f);

	auto base_mesh = graphics->newMeshWithIdentifier("rings.tcf/base");

	auto base_model = graphics->newModel();
	base_model->material = base_material;
	base_model->mesh = base_mesh;

	base_actor_ = std::make_shared<tyga::Actor>();
	base_actor_->attachComponent(base_model);
	world->addActor(base_actor_);
	/////////////////////////////////////////////////////////////////////////
	//stand.

	stand_actors_.resize(3);
		outer_actors_.resize(3);
		middle_actors_.resize(3);
		inner_actors_.resize(3);


	for (int i = 0; i < 3; i++) 
	{
	auto stand_material = graphics->newMaterial();
	stand_material->colour = tyga::Vector3(0.f, 1.f, 0.f);

	auto stand_mesh = graphics->newMeshWithIdentifier("rings.tcf/stand");

	auto stand_model = graphics->newModel();
	stand_model->material = stand_material;
	stand_model->mesh = stand_mesh;

	stand_actors_[i] = std::make_shared<tyga::Actor>();
	stand_actors_[i]->attachComponent(stand_model);
	world->addActor(stand_actors_[i]);

	///////////////////////////////////////////////////////////////////////////
	// outer ring.



		auto outer_material = graphics->newMaterial();
		outer_material->colour = tyga::Vector3(0.f, 1.f, 1.f);

		auto outer_mesh = graphics->newMeshWithIdentifier("rings.tcf/outer");

		auto outer_model = graphics->newModel();
		outer_model->material = outer_material;
		outer_model->mesh = outer_mesh;

		outer_actors_[i] = std::make_shared<tyga::Actor>();
		outer_actors_[i]->attachComponent(outer_model);
		world->addActor(outer_actors_[i]);
	
	////////////////////////////////////////////////////////////////////////////
	//middle ring.

	



			auto middle_material = graphics->newMaterial();
			middle_material->colour = tyga::Vector3(1.f, 0.2f, 1.f);

			auto middle_mesh = graphics->newMeshWithIdentifier("rings.tcf/middle");

			auto middle_model = graphics->newModel();
			middle_model->material = middle_material;
			middle_model->mesh = middle_mesh;

			middle_actors_[i] = std::make_shared<tyga::Actor>();
			middle_actors_[i]->attachComponent(middle_model);
			world->addActor(middle_actors_[i]);
		
	/////////////////////////////////////////////////////////////////////////
	//inner ring.

		

	
			auto inner_material = graphics->newMaterial();
			inner_material->colour = tyga::Vector3(1.f, 2.f, 0.2f);

			auto inner_mesh = graphics->newMeshWithIdentifier("rings.tcf/inner");

			auto inner_model = graphics->newModel();
			inner_model->material = inner_material;
			inner_model->mesh = inner_mesh;

			inner_actors_[i] = std::make_shared<tyga::Actor>();
			inner_actors_[i]->attachComponent(inner_model);
			world->addActor(inner_actors_[i]);
		}
	////////////////////////////////////////////////////////////////////////
}

void RingsOfTime::
actorWillLeaveWorld(std::shared_ptr<tyga::Actor> actor)
{
}

void RingsOfTime::
actorClockTick(std::shared_ptr<tyga::Actor> actor)
{
    const float time = tyga::BasicWorldClock::CurrentTime();
    const float delta_time = tyga::BasicWorldClock::CurrentTickInterval();

    // the delegate's actor's transformation acts as the root of the hierarchy
    auto root_xform = actor->Transformation();

    /*
     * Tutorial: You will replace this animation during the first tutorial
     *           activity "Upgrade Existing Animation".
     */




   
	
	for (int i = 0; i < 3; i++) {
		// th next 4 lies positio the sad and rings in there rig osition and rotate them i th x,y,z postiton while makei them a parent of what came before them.
		float base_x = Ryan_Mcdonnell::continuous(-3.f, 0.7f, time);
		auto base_xform = root_xform * Ryan_Mcdonnell::rotateY(0.25 * M_PI * time);
		tyga::Matrix4x4 stand_xform = Ryan_Mcdonnell::rotateY(0.25 * M_PI * time) * Ryan_Mcdonnell::translate(8, 0.3, 0) * Ryan_Mcdonnell::rotateY((float)(i + 1) * 120 * M_PI / 180) * base_xform;
		tyga::Matrix4x4 outer_xform = Ryan_Mcdonnell::rotateX(0.25 * M_PI * time) * Ryan_Mcdonnell::translate(0, 5, 0) * stand_xform;
		tyga::Matrix4x4 middle_xform = Ryan_Mcdonnell::rotateZ(0.25 * M_PI * time) * Ryan_Mcdonnell::translate(0, 0, 0) * outer_xform;
		tyga::Matrix4x4 inner_xform = Ryan_Mcdonnell::rotateX(0.25 * M_PI * time) * Ryan_Mcdonnell::translate(0, 0, 0) * middle_xform;

		// pass the actors into the xforms to be used to move them etc...(see above)
		base_actor_->setTransformation(base_xform);
		stand_actors_[i]->setTransformation(stand_xform);
		outer_actors_[i]->setTransformation(outer_xform);
		middle_actors_[i]->setTransformation(middle_xform);
		inner_actors_[i]->setTransformation(inner_xform);

	}
}
