<script setup lang="ts">
import Ping from '~/components/icons/Ping.vue'
import Tilt from '~/components/icons/Tilt.vue'
import Waste from '~/components/icons/Waste.vue'
import Bin from '~/components/icons/Bin.vue'

const { data, refresh } = useFetch('/api/data')
const lastPing = ref(0)

const history = computed(() => {
    const nums = data.value.history.dists

    const a = {
        labels: data.value.history.labels.map(l => l),
        dists: nums.map((st: string) => parseInt(st)),
    }

    return a
})

const toggleFan = async () => {
    await $fetch('/api/toggleFan')

    refresh()
}

let interval: NodeJS.Timeout
onMounted(() => {
    interval = setInterval(() => {
        refresh()
        lastPing.value = Date.now()
    }, 2000)
})

onUnmounted(() => clearInterval(interval))

const lastUpdatedComp = computed(() => {
    const last = (Date.now() - lastPing.value) / 1000

    console.log(lastUpdatedComp)
    if (last > 10) return 0

    return last
})
</script>

<template>
    <div class="max-w-7xl mx-auto space-y-4">
        <UiHeader />

        <UiTiltAlert v-if="data?.tilted" />

        <div class="grid grid-cols-3 gap-4">
            <UiCard
                title="Lid Status"
                :value="data?.lidOpen ? 'Open' : 'Closed'"
                value-color="#000000"
                :icon="Bin"
            />
            <UiCard
                title="Tilt Status"
                :value="data?.tilted ? `Unstable` : `Stable`"
                :value-color="data?.tilted ? '#d03737' : '#49d037'"
                :icon="Tilt"
            />
            <!--                value-color="#49d037" -->
            <!--            /> -->
            <UiCard
                title="Photoresistor"
                :value="`${data?.photoresistor}`"
                value-color="#000000"
                :icon="Waste"
            />
        </div>

        <div class="grid grid-cols-2 gap-4">
            <UiSensor
                title="Bin Capacity"
                subtitle="Bin waste capacity detection"
                label="Current Capacity"
                :label-text="`${data?.capacity}%`"
                :value="data?.capacity || 0"
            />

            <UiSensor
                title="Temperature Sensor"
                subtitle="Bin heat measurement"
                label="Current Temperature"
                :label-text="`${data?.temperature}°`"
                :value="data?.temperature || 0"
            />
        </div>

        <div class="p-4 bg-white border border-gray-300 rounded lg">
            <h2 class="text-2xl font-semibold">
                Fan Controls
            </h2>

            <p>Forced fan state: {{ data.fanState }}</p>
            <button
                class="bg-blue-600 text-white font-medium py-2 px-4 rounded"
                @click="toggleFan"
            >
                Toggle
            </button>
        </div>

        <div class="p-4 bg-white border border-gray-300 rounded-lg">
            <h2 class="font-semibold text-lg">
                Waste Analytics
            </h2>
            <ChartsLineChart :data="history" />
        </div>
    </div>
</template>

<style scoped>

</style>
