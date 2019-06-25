{
  "targets": [
    {
      "target_name": "DistanceSensor",
      "sources": [
          "src/wrapper/addon.cpp",
          "src/wrapper/MyObject.cpp",
          "src/lib/DistanceSensor.cpp",
          "src/lib/robotois-digital-header/DigitalHeader.cpp",
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
