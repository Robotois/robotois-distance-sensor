{
  "targets": [
    {
      "target_name": "DistanceSensor",
      "sources": [ "src/Wrapper/DistanceSensor.cpp","src/Wrapper/DistanceWrapper.cpp",
      "src/Modules/Distance/DistanceSensor.cpp",
      "src/Libraries/DigitalIO/DigitalHeader.cpp",
      "src/Libraries/Timer/AccurateTiming.cpp"
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
