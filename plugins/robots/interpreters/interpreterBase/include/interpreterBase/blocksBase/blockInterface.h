#pragma once

#include <QtCore/QObject>

#include <qrkernel/ids.h>
#include <interpreterBase/robotModel/portInfo.h>
#include <interpreterBase/robotModel/deviceInfo.h>
#include <interpreterBase/interpreterBaseDeclSpec.h>

namespace interpreterBase {
namespace blocksBase {

/// An interface of the block`s implementation used in the interprer for executing it.
class ROBOTS_INTERPRETER_BASE_EXPORT BlockInterface : public QObject
{
	Q_OBJECT

public:
	virtual ~BlockInterface() {}

	/// Starts block execution.
	virtual void interpret() = 0;

	/// Called each time when the interpretation process fails for some reason.
	/// Block must deinitialize its recources here.
	virtual void setFailedStatus() = 0;

	/// Returns the diagram`s id of the block whitch is impemented by this object.
	virtual qReal::Id const id() const = 0;

	/// Returns an information about the devices that must be configured for correct work of this block.
	virtual QMap<robotModel::PortInfo, robotModel::DeviceInfo> usedDevices() const = 0;

	/// Called each time when control flow has reached the end block of the requested for stepping into diagram.
	virtual void finishedSteppingInto() = 0;

signals:
	/// Emitted each time when the block has finished its work.
	/// @param nextBlock An id of the block that was decided to follow next.
	void done(qReal::Id const &nextBlock);

	/// Emitted each time when the block has requested new thread. Useful for fork blocks.
	/// @param startBlock An id of the block that was decided to start the thread execution.
	void newThread(qReal::Id const &startBlock);

	/// Emitted each time when the block stops its execution due to some error.
	void failure();

	/// Emitted each time when execution must be continued from the initial block
	/// of the specified diagram
	void stepInto(qReal::Id const &diagram);
};

}
}