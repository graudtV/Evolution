#pragma once

#include "Abstract/IGameObject.h"
#include <list>

namespace evo {
namespace snake {

class ISnakeKernel;

class SnakeBody {
public:
	using SegmentList = std::list<Coord>;

	explicit SnakeBody(const SegmentList& segments) :
		m_segments(segments) {}

	template <class InputIt>
	SnakeBody(InputIt fst, InputIt last) :
		m_segments(fst, last) {}

	Coord head() const { return m_segments.front(); }	
	Coord tail() const { return m_segments.back(); }

	void push_head(Coord coord) { m_segments.push_front(coord); }
	void pop_tail() { m_segments.pop_back(); }

	const SegmentList& segments() const { return m_segments; }

private:
	SegmentList m_segments;
};

enum class SnakeDirection {
	eUp,
	eDown,
	eLeft,
	eRight
};

class Snake : public IGameObject {
public:
	Snake(const SnakeBody& body);

	void attach_kernel(ISnakeKernel& kernel);
	void detach_kernel();
	bool is_kernel_attached() const { return m_kernel != nullptr; }
	ISnakeKernel *kernel() { return m_kernel; }

	const SnakeBody& staging_body() const { return m_staging_body; }
	const SnakeBody& visible_body() const { return m_visible_body; }

protected:
	void make_move() override;

private:
	SnakeBody m_staging_body;
	SnakeBody m_visible_body;
	ISnakeKernel *m_kernel;
};

} // snake namespace end
} // evo namespace end