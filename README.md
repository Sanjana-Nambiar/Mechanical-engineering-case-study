# Mechanical Engineering Case Study Flight Simulator Wind Speed

## Step 1: Problem Identification and Statement
The goal of this assignment is to develop a software to generate a computer simulation of wind speed for a flight simulator, this includes creating data for wind speed, storm and microburst. This program is also aimed at identifying the storm.

## Step 2: Gathering of Information and Input/output Description
#### Relevant information:
A flight simulator is a device that artificially re-creates aircraft flight and the environment in which it flies, for pilot training, design, or other purposes. It includes replicating the equations that govern how aircraft fly, how they react to applications of flight controls, the effects of other aircraft systems, and how the aircraft reacts to external factors such as air density, turbulence, wind shear, cloud, precipitation, etc.

Flight simulation is used for a variety of reasons, including flight training (mainly of pilots), the design and development of the aircraft itself, and research into aircraft characteristics and control handling qualities. The purpose of simulation is not to completely substitute for actual flight training but to thoroughly familiarize students with the vehicle concerned before they undergo expensive and possibly dangerous actual flight training. Simulation also is useful for review and for familiarizing pilots with new modifications to existing craft.

### Input/output Description:
#### The inputs are:
- The “simulationConfiguration.txt” that contains all the data, i.e.;
  - Average Wind Speed
  - Gust Value
  - Simulation Duration
  - Step Size
  - Storm Probability
  - Min and Max Storm Amplitude
  - Min and Max Storm Duration
  - Microburst Probability
  - Min and Max Microburst Amplitude
  - Min and Max Microburst Duration

#### The outputs are:
- WindSpeedData.txt
  - Time
  - Wind Speed 
- StormData.txt
  - Time
  - Storm Magnitude
- Storm Probability
- BurstData.txt 
  - Time
  - Microburst Magnitude
  - Microburst Probability 
- WindSimulation.txt
  - Time
  - Wind Simulation
  - Binary Value
