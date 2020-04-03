#Piping

Piping is the part of the framework that connects diferent elements together.
These connections can be made programatically and, once the connection is
completed, it will be restored between power cycles. To do so, the piping
manager will build an xml describing each connection.

The following diagram shows the connection between inputs and outputs of three
diferent elements.

```xml
<diagram>
    <server name="TemperatureSensor">
        <connection>
            <output>Temperature</output>
            <client name="SignalsManager">
                <input>Temperature[1]</input>
            </client>
            <client name="Thermostat">
                <input>Sensor</input>
            </client>
            <client name="MyApp">
                <input>Temperature[1]</input>
            </client>
        </connection>
    </server>    
    <server name="MyApp">
        <connection>
            <output>Heat</output>
            <client name="Switch_1">
                <input>Close</input>
            </client>
        </connection>
    </server>  
    <server name="Switch_1">
        <connection>
            <output>IsClosed</output>
            <client name="MyApp">
                <input>HeatIsOn</input>
            </client>
        </connection>
    </server>
</diagram>
```

When the system boots up and all the elements have been instantiated, the
piping manager will start connectig elements together.

