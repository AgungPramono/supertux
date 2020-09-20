//  SuperTux - Particle zone : Spawn
//  Copyright (C) 2020 A. Semphris <semphris@protonmail.com>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_SUPERTUX_OBJECT_PARTICLE_ZONE_HPP
#define HEADER_SUPERTUX_OBJECT_PARTICLE_ZONE_HPP

#include "squirrel/exposed_object.hpp"
// TODO: #include "scripting/wind.hpp"
#include "supertux/moving_object.hpp"

class ReaderMapping;

/** Defines an area where a certain particle type can spawn */
class ParticleZone final :
  public MovingObject//, // TODO: Make this area actually moveable with Squirrel
  //public ExposedObject<ParticleZone, scripting::Wind> // TODO: Scripting interface
{
public:
  ParticleZone(const ReaderMapping& reader);

  virtual void update(float dt_sec) override;
  virtual void draw(DrawingContext& context) override;

  virtual bool has_variable_size() const override { return true; }
  virtual std::string get_class() const override { return "particle-zone"; }
  virtual std::string get_display_name() const override { return _("Particle zone");}
  virtual HitResponse collision(GameObject& other, const CollisionHit& hit) override;

  virtual ObjectSettings get_settings() override;
  
  Rectf get_rect() {return m_col.m_bbox;}

  enum class ParticleZoneType {
    /** Particles will spawn in this area */
    Spawn,
    /** TODO: Particles will die if they leave this area */
    Life,
    /** TODO: Particles will disappear instantly if they leave this area */
    LifeClear,
    /** Particles will start dying if they touch this area */
    Killer,
    /** Particles will disappear instantly if they touch this area */
    Destroyer
  };

  /** @name Scriptable Methods
      @{ */

  /** Sets whether or not particles can spawn in this area */
  void set_enabled(bool enabled) {m_enabled = enabled;}

  /** Returns whether or not particles can spawn in this area */
  bool get_enabled() const {return m_enabled;}

  /** Sets the name of the particle object for this area */
  void set_particle_name(std::string& particle_name) {m_particle_name = particle_name;}

  /** Returns the name of the particle object for this area */
  std::string get_particle_name() const {return m_particle_name;}

  /** Move the area around. Multiple calls stack (e. g. calling one before
   *  the other finished will play both movements simultaneously)
   */
  //void displace(int x, int y, float time, std::string easing);

  /** Resize the area. Multiple calls stack (e. g. calling one before
   *  the other finished will play both resizes simultaneously)
   */
  //void resize(int width, int height, float time, std::string easing);

  /** Returns the current X position of the zone */
  float current_x() {return m_col.m_bbox.get_left();}

  /** Returns the current Y position of the zone */
  float current_y() {return m_col.m_bbox.get_top();}

  /** Returns the target X position of the zone */
  //float target_x() {return m_col.m_bbox.get_left();}

  /** Returns the target Y position of the zone */
  //float target_y() {return m_col.m_bbox.get_left();}

  /** @} */

  void set_type(ParticleZoneType type) {m_type = type;}
  ParticleZoneType get_type() {return m_type;}

private:
  bool m_enabled;
  std::string m_particle_name;
  ParticleZoneType m_type;

private:
  ParticleZone(const ParticleZone&) = delete;
  ParticleZone& operator=(const ParticleZone&) = delete;
};

#endif

/* EOF */
