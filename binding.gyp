{
  "targets": [
    {
      "target_name": "DistanceSensor",
      "sources": [
          "src/wrapper/DistanceSensor.cpp",
          "src/wrapper/DistanceWrapper.cpp",
          "src/DistanceSensor.cpp",
          "src/libraries/robotois-digital-header/DigitalHeader.cpp",
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
