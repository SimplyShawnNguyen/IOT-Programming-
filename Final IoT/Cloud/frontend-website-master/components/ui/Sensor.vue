<script setup lang="ts">
const props = defineProps<{
    title: string
    subtitle: string
    label: string
    labelText: string
    value: number
}>()

const progress = computed(() => {
    return `${props.value}%`
})
</script>

<template>
    <div class="bg-white border border-gray-200 rounded-lg py-7 px-6 space-y-2">
        <div class="flex flex-col">
            <h2 class="font-semibold text-2xl">
                {{ props.title }}
            </h2>
            <p class="text-gray-500 font-normal">
                {{ props.subtitle }}
            </p>
        </div>

        <div class="space-y-3 mt-4">
            <div class="flex justify-between">
                <span>{{ props.label }}</span>
                <span>{{ props.labelText }}</span>
            </div>

            <div class="h-2 rounded-full w-full bg-gray-200">
                <div class="bar bg-black h-full w-[30%] rounded-full" />
            </div>
        </div>
    </div>
</template>

<style scoped>
.bar {
    width: v-bind(progress);
}
</style>
