<script setup lang="ts">
import chart from 'chart.js/auto'
import { onMounted } from 'vue'

const props = defineProps<{ data: { labels: string[], dists: number[] } }>()

onMounted(async () => {
    const v = {
        labels: props.data.labels,
        datasets: [{
            label: 'Waste Level',
            data: props.data.dists,
            fill: true,
            tension: 0.1,
        }],
    }
    const lineChart = new chart(
        document.getElementById('canvas-g1') as HTMLCanvasElement,
        {
            type: 'line',
            data: v,
        },
    )

    watch(() => props.data, (newData) => {
        lineChart.data.labels = newData.labels
        lineChart.data.datasets[0].data = newData.dists
        lineChart.update()

        console.log(lineChart.data)
    })
})
</script>

<template>
    <canvas id="canvas-g1" />
</template>

<style scoped>

</style>
