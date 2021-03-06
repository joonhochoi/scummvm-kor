/* ScummVM - Graphic Adventure Engine
*
* ScummVM is the legal property of its developers, whose names
* are too numerous to list here. Please refer to the COPYRIGHT
* file distributed with this source distribution.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*/

#ifndef COMMON_HARDWARE_KEY_H
#define COMMON_HARDWARE_KEY_H

#include "common/scummsys.h"

#ifdef ENABLE_KEYMAPPER

#include "common/keyboard.h"
#include "common/list.h"
#include "common/str.h"
#include "common/textconsole.h"

namespace Common {

typedef uint32 HardwareInputCode;

enum HardwareInputType {
	/** Input that sends single events */
	kHardwareInputTypeGeneric,
	/** Input that usually send -up and -down events */
	kHardwareInputTypeKeyboard
};

/**
* Describes an available hardware input
*/
struct HardwareInput {
	/** unique id used for saving/loading to config */
	String id;

	/** Human readable description */
	String description;

	const HardwareInputType type;

	/**
	 * A platform specific unique identifier for an input event
	 * generated when this input is triggered.
	 * This is only relevant when type == kHardwareInputTypeGeneric
	 */
	HardwareInputCode inputCode;

	/**
	 * The KeyState that is generated by the back-end
	 * when this hardware key is pressed.
	 * This is only relevant when type == kHardwareInputTypeKeyboard
	 */
	KeyState key;

	HardwareInput(String i, HardwareInputCode ic = 0, String desc = "")
		: id(i), inputCode(ic), description(desc), type(kHardwareInputTypeGeneric) { }

	HardwareInput(String i, KeyState ky, String desc = "")
		: id(i), key(ky), description(desc), type(kHardwareInputTypeKeyboard) { }
};

struct HardwareInputTableEntry {
	const char *hwId;
	HardwareInputCode code;
	const char *desc;
};

/**
 * Entry in a static table of available non-modifier keys
 */
struct KeyTableEntry {
	const char *hwId;
	KeyCode keycode;
	uint16 ascii;
	const char *desc;
	bool shiftable;
};

/**
 * Entry in a static table of available key modifiers
 */
struct ModifierTableEntry {
	byte flag;
	const char *id;
	const char *desc;
	bool shiftable;
};

/**
 * Simple class to encapsulate a device's set of HardwareInputs.
 * Each device should instantiate this and call addHardwareInput a number of times
 * in its constructor to define the device's available keys.
 */
class HardwareInputSet {
public:

	/**
	 * Add hardware input keys to the set out of key and modifier tables.
	 * @param useDefault	auto-add the built-in default inputs
	 * @param keys       	table of available keys
	 * @param modifiers  	table of available modifiers
	 */
	HardwareInputSet(bool useDefault = false, const KeyTableEntry keys[] = 0, const ModifierTableEntry modifiers[] = 0);

	virtual ~HardwareInputSet();

	void addHardwareInput(const HardwareInput *input);

	const HardwareInput *findHardwareInput(String id) const;

	const HardwareInput *findHardwareInput(const HardwareInputCode code) const;

	const HardwareInput *findHardwareInput(const KeyState& keystate) const;

	const List<const HardwareInput *> &getHardwareInputs() const { return _inputs; }

	uint size() const { return _inputs.size(); }

	/**
	 * Add hardware inputs to the set out of a table.
	 * @param inputs       table of available inputs
	 */
	void addHardwareInputs(const HardwareInputTableEntry inputs[]);

	/**
	 * Add hardware inputs to the set out of key and modifier tables.
	 * @param keys       table of available keys
	 * @param modifiers  table of available modifiers
	 */
	void addHardwareInputs(const KeyTableEntry keys[], const ModifierTableEntry modifiers[]);

	void removeHardwareInput(const HardwareInput *input);

private:

	List<const HardwareInput *> _inputs;
};

} // End of namespace Common

#endif // #ifdef ENABLE_KEYMAPPER

#endif // #ifndef COMMON_HARDWARE_KEY_H
