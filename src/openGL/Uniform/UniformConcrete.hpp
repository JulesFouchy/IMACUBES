#pragma once

#include "Uniform.hpp"

#include <string>
#include <tuple>
#include "Debugging/Log.hpp"
#include "imgui.h"

template <typename T>
class UniformConcrete : public Uniform {
friend class UniformDescription;
template <typename T>
friend class UniformDescriptionConcrete;
public:
	UniformConcrete() = default;
	UniformConcrete(int shaderIndex, const std::string& nameInsideStruct, T value, T minValue, T maxValue)
		: Uniform(shaderIndex, nameInsideStruct), m_value(value), m_valueBeforeEditingStarted(value), m_minValue(minValue), m_maxValue(maxValue)
	{}

	void set(int structIndex) override;

	void ImGui_Slider() override;

	Uniform* createPtrWithSameData() override {
		return new UniformConcrete<T>(m_shaderIndex, getNameInsideStruct(), m_value, m_minValue, m_maxValue);
	}

	inline T& value() { return m_value; }
private:
	void pushChangeInHistory_IfNecessary() {
		if (ImGui::IsItemDeactivatedAfterEdit()) {
			History& history = Locate::history();
			history.beginUndoGroup();
			T val = m_value;
			T prevVal = m_valueBeforeEditingStarted;
			history.addAction(Action(
				// DO action
				[this, val]()
			{
				this->m_value = val;
			},
				// UNDO action
				[this, prevVal]()
			{
				this->m_value = prevVal;
			}
			));
			history.endUndoGroup();
			m_valueBeforeEditingStarted = m_value; // ready for next edit
		}
	}
private:
	T m_value;
	T m_valueBeforeEditingStarted;
	T m_minValue;
	T m_maxValue;
};