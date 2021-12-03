import os
import sys

with open('./.idea/runConfigurations/baseConfig', 'r') as file:
    baseData = file.read()

for i in range(25, 26):
    configData = baseData.replace("%NAME%", f"Day{i} First").replace("%DAY%", f"Day{i}").replace("%PAR%",
                                                                                                 "--one").replace(
        "%SAMPLE%", "")

    with open(f"./.idea/runConfigurations/Day{i}_First.xml", "w") as file:
        file.write(configData)

    configData = baseData.replace("%NAME%", f"Day{i} Second").replace("%DAY%", f"Day{i}").replace("%PAR%",
                                                                                                  "--two").replace(
        "%SAMPLE%", "")

    with open(f"./.idea/runConfigurations/Day{i}_Second.xml", "w") as file:
        file.write(configData)

    configData = baseData.replace("%NAME%", f"Day{i} Sample First").replace("%DAY%", f"Day{i}").replace("%PAR%",
                                                                                                        "--one").replace(
        "%SAMPLE%", "sample_")

    with open(f"./.idea/runConfigurations/Day{i}_Sample_First.xml", "w") as file:
        file.write(configData)

    configData = baseData.replace("%NAME%", f"Day{i} Sample Second").replace("%DAY%", f"Day{i}").replace("%PAR%",
                                                                                                         "--two").replace(
        "%SAMPLE%", "sample_")

    with open(f"./.idea/runConfigurations/Day{i}_Sample_Second.xml", "w") as file:
        file.write(configData)
