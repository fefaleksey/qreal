/* Copyright 2013-2016 CyberTech Labs Ltd., Grigorii Zimin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "trikEnginesBackwardBlock.h"

#include <kitBase/robotModel/robotParts/motor.h>

using namespace trik::blocks::details;
using namespace kitBase::robotModel::robotParts;

TrikEnginesBackwardBlock::TrikEnginesBackwardBlock(kitBase::robotModel::RobotModelInterface &robotModel)
	: EngineCommandBlock(robotModel)
{
}

void TrikEnginesBackwardBlock::run()
{
	const auto result = -eval<int>("Power");
	if (!errorsOccured()) {
		MotorsAggregator *aggregator = findMotorsAggregator();
		const QList<Motor *> ports = parsePorts<Motor>();
		if (aggregator) {
			QList<QPair<QString, int>> portsWithPowers;
			for (Motor * const motor : ports) {
				portsWithPowers.append(qMakePair<QString, int>(motor->port().name(), result));
			}

			aggregator->on(portsWithPowers);
		} else {
			for (Motor * const motor : ports) {
				motor->on(result);
			}
		}

		emit done(mNextBlockId);
	}
}
