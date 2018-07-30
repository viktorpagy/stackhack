#pragma once

namespace SDK
{
	class CUserCmd;
	class CBaseEntity;
	class CBaseWeapon;
}

struct Info
{
	Info() {}

	SDK::CAnimationLayer backup_layer, prev_layer;
	Vector last_lby, inverse, inverse_right, inverse_left, lby, back, left, right, backtrack;
	float stored_simtime, last_move_time, pre_anim_lby;
	int last_ammo;
	bool breaking_lby, reset_state, could_be_faking;
	std::vector<float> unresolved_yaw, lby_deltas;

	bool lby_changed;
	bool could_be_slowmo;
	bool is_moving;
	bool is_standing;
	bool is_jumping;
	bool is_crouching;
	bool lby_updated;
	bool using_fake_angles;
	float last_moving_lby;
	float stored_lby;
	float next_lby_update_time;
	int stored_missed;
};


struct ResolveInfo
{
	ResolveInfo()
	{
		m_bActive = false;

		m_flVelocity = 0.f;
		m_vecVelocity = Vector(0, 0, 0);
		m_angEyeAngles = QAngle(0, 0, 0);
		m_flSimulationTime = 0.f;
		m_flLowerBodyYawTarget = 0.f;

		m_flStandingTime = 0.f;
		m_flMovingLBY = 0.f;
		m_flLbyDelta = 180.f;
		m_bIsMoving = false;

		m_angDirectionFirstMoving = QAngle(0, 0, 0);
		m_nCorrectedFakewalkIdx = 0;

	}



	bool operator==(const ResolveInfo &other)
	{
		return other.m_flSimulationTime == m_flSimulationTime;
	}

	bool m_bActive;

	float_t m_flVelocity;
	Vector m_vecVelocity;
	QAngle m_angEyeAngles;
	float_t m_flSimulationTime;

	int32_t m_iLayerCount = 0;
	SDK::CAnimationLayer animationLayer[15];
	float_t m_flStandingTime;
	float_t m_flMovingLBY;
	float_t m_flLbyDelta;
	bool m_bIsMoving;
	QAngle m_angDirectionFirstMoving;
	int32_t m_nCorrectedFakewalkIdx;
	float_t m_flLowerBodyYawTarget;

	int32_t m_nShotsMissed = 0;
};


class CResolver
{
public:
	Info player_info[65];
	void record(SDK::CBaseEntity * entity, float new_yaw);
	void resolve(SDK::CBaseEntity* entity, int i);
};

extern CResolver* resolver;